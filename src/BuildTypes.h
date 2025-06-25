
#pragma once

#include <cassert>
#include "HeaderGlobals.h"
#include "SourceLocation.h"

typedef int DataType;

/* Don't change the order of these types without updating the code below accordingly.
   In another words, don't change it.
 */
enum BasicDataType {tvoid, tbool, tchar,
  tint8, tint16, tint32, tint64, 
  tint2u, tint3u, tint4u, tint5u, tint6u, tint7u, tint8u,
  tint9u, tint10u, tint11u, tint12u, tint13u, tint14u, tint15u, tint16u,
  tint17u, tint18u, tint19u, tint20u, tint21u, tint22u, tint23u, tint24u,
  tint25u, tint26u, tint27u, tint28u, tint29u, tint30u, tint31u, tint32u,
  tint64u,
  tfloat, tdouble, tldouble,
  /* new types here! */
  tobject,
  __bdt_last};

enum DataQualifier {qnone, qconst, qvolatile};
typedef DataQualifier DataQualifier;

struct DataTypeInfo {
    string name;
    unsigned bitWidth;
    Type *llvmType;
    unsigned dwarfEnc;
    DIType *diType;
    DIDerivedType *diPointerType;
    SourceLocation *sl;
    bool isDefined;
    bool isComplex;
    bool isEnum;
    bool isInterface;
    bool isInternal;
    unsigned char arrayDimensions;

    DataTypeInfo() {}

    DataTypeInfo(string name) {
        this->name = name;
        this->bitWidth = 0;
        this->llvmType = NULL;
        this->dwarfEnc = 0;
        this->diType = NULL;
        this->diPointerType = NULL;
        this->isDefined = false;
        this->isComplex = false;
        this->isEnum = false;
        this->isInternal = false;
        this->isInterface = false;
        this->arrayDimensions = 0;
    }

    DataTypeInfo(const char* name, unsigned bitWidth, Type *llvmType, unsigned dwarfEnc):
        name(name), bitWidth(bitWidth), llvmType(llvmType), dwarfEnc(dwarfEnc), diType(NULL),
        diPointerType(NULL), sl(NULL), isDefined(true), isComplex(false), isInternal(false),
        isInterface(false), isEnum(false), arrayDimensions(0) {};
};

class Program;

class BuildTypes {
private:
    map<DataType, DataTypeInfo> tinfo;
    map<string, DataType> namedTypes;
    DataType nextt = __bdt_last;
    DataType targetPointerType;

    DataType addDataType(const DataTypeInfo& udt) {
        DataType result = nextt++;
        tinfo[result] = udt;
        namedTypes[udt.name] = result;
        return result;
    }

    void generateDebugInfoForEnum(DataTypeInfo &info, Node *userType);
    void generateDebugInfoForUserType(DataTypeInfo &info, Node *userType);

public:
    static const DataType undefinedType = -1;

    BuildTypes(DataType targetPointerType, Program *program);

    DataType addDataType(Node* userType, Type* llvmType, 
        unsigned typeBitWidth = 0, bool isEnum = false);

    DataType getType(const string& name, bool createUndefined = false);

    DataType getArrayType(const string& elementName, SourceLocation n,
        unsigned char dimensions, bool createUndefined = false);

    DataType getArrayElementType(DataType arrayDt);

    const char *name(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].name.c_str();
    }

    void updateName(DataType tid, const string& name) {
        namedTypes.erase(tinfo[tid].name);
        tinfo[tid].name = name;
        namedTypes[name] = tid;
        StructType *st = dyn_cast<StructType>(llvmType(tid));
        if (st)
            st->setName(name);
    }

    const unsigned bitWidth(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].bitWidth;
    }

    Type *llvmType(DataType tid);

    DIType *diType(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].diType;
    }

    DIDerivedType *diPointerType(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].diPointerType;
    }

    SourceLocation *location(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].sl;
    }

    bool isPrimitiveType(DataType tid) const {
        return tid >= tbool && tid < __bdt_last;
    }

    bool isNumericDataType(DataType tid) {
        return (tid >= tbool && tid <= tldouble) || isEnum(tid);
    }

    bool isIntegerDataType(DataType tid) const {
        return tid >= tbool && tid <= tint64u;
    }

    bool isSignedDataType(DataType tid) const {
        return (tid >= tint8 && tid <= tint64);
    }

    bool isUnsignedDataType(DataType tid) const {
        return (tid >= tint2u && tid <= tint64u) || (tid == tchar) || (tid == tbool);
    }

    bool isFloatDataType(DataType tid) const {
	    return tid >= tfloat && tid <= tldouble;
    }

    bool isComplex(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].isComplex;
    }
    
    bool isEnum(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].isEnum;
    }

    bool isInternal(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].isInternal;
    }

    void setInternal(DataType tid, bool v) {
        assert(tid != -1 && "Undefined type");
        tinfo[tid].isInternal = v;
    }

    void setInterface(DataType tid, bool v) {
        assert(tid != -1 && "Undefined type");
        tinfo[tid].isInterface = v;
    }

    bool isInterface(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].isInterface;
    }

    bool isUserType(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].isComplex && !tinfo[tid].isInterface;
    }

    bool isArray(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].arrayDimensions == 1;
    }

    bool isMatrix(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].arrayDimensions == 2;
    }

    bool isArrayOrMatrix(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].arrayDimensions > 0;
    }

    unsigned char dimensions(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].arrayDimensions; 
    }

    DataType unsignedToSigned(DataType tid) {
        assert(isUnsignedDataType(tid));
        switch (tid) {
            case tchar:
                return tint8;
            case tint2u:
            case tint3u:
            case tint4u:
            case tint5u:
            case tint6u:
            case tint7u:
            case tint8u:
                return tint8;
            case tint16u:
                return tint16;
            case tint32u:
                return tint32;
            case tint64u:
            default:
                return tint64;
        }
    }

    DataType signedToUnsigned(DataType tid) {
        assert(isSignedDataType(tid));
        if (tid == tbool)
            return tid;
        switch (tid) {
            case tint8:
                return tint8u;
            case tint16:
                return tint16u;
            case tint32:
                return tint32u;
            case tint64:
            default:
                return tint64u;
        }
    }

    bool isDefined(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].isDefined; 
    }

    unsigned getTargetPointerBitWidth() {
        return tinfo[targetPointerType].bitWidth;
    }

    void generateDebugInfoForTypes();

    bool isArrayCompatible(DataType srcDt, DataType destDt);
};

// TODO: Replace all places with buildType::name
static string getTypeName(Type *ty) {
	string type_str;
	llvm::raw_string_ostream rso(type_str);
	ty->print(rso);
	return rso.str();
}
