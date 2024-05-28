
#pragma once

#include <cassert>
#include "HeaderGlobals.h"
#include "SourceLocation.h"

typedef int DataType;

enum BasicDataType {tvoid, tbool, tchar, tint2, tint3, tint4, tint5, tint6, tint7, 
  tint8, tint16, tint32, tint64, tint8u, tint16u, tint32u, tint64u, 
  tfloat, tdouble, tldouble,
  /* new types here! */
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
        this->isInternal = false;
        this->isInterface = false;
        this->arrayDimensions = 0;
    }

    DataTypeInfo(const char* name, unsigned bitWidth, Type *llvmType, unsigned dwarfEnc):
        name(name), bitWidth(bitWidth), llvmType(llvmType), dwarfEnc(dwarfEnc), diType(NULL),
        diPointerType(NULL), sl(NULL), isDefined(true), isComplex(false), isInternal(false),
        isInterface(false), arrayDimensions(0) {};
};

class BuildTypes {
private:
    map<DataType, DataTypeInfo> tinfo;
    map<string, DataType> namedTypes;
    DataType nextt = __bdt_last;

    DataType addDataType(const DataTypeInfo& udt) {
        DataType result = nextt++;
        tinfo[result] = udt;
        namedTypes[udt.name] = result;
        return result;
    }

public:
    static const DataType undefinedType = -1;

    BuildTypes(DataType targetPointerType);

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

    bool isIntegerDataType(DataType tid) const {
        return tid >= tint8 && tid <= tint64u;
    }

    bool isSignedDataType(DataType tid) const {
        return tid >= tint8 && tid <= tint64;
    }

    bool isUnsignedDataType(DataType tid) const {
        return tid >= tint8u && tid <= tint64u;
    }

    bool isFloatDataType(DataType tid) const {
	    return tid >= tfloat && tid <= tldouble;
    }

    bool isComplex(DataType tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].isComplex;
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
};

// TODO: Replace all places with buildType::name
static string getTypeName(Type *ty) {
	string type_str;
	llvm::raw_string_ostream rso(type_str);
	ty->print(rso);
	return rso.str();
}
