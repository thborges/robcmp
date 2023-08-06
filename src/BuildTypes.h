
#pragma once

#include <cassert>
#include "HeaderGlobals.h"

typedef int DataType;

enum BasicDataType {tvoid, tbool, tchar, tint2, tint8, tint16, tint32, tint64, 
  tint8u, tint16u, tint32u, tint64u, tfloat, tdouble, tldouble, tarray,
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
    SourceLocation *sl;
    bool isDefined;
    bool isComplex;

    DataTypeInfo() {}

    DataTypeInfo(string name) {
        this->name = name;
        this->bitWidth = 0;
        this->llvmType = NULL;
        this->dwarfEnc = 0;
        this->diType = NULL;
        this->isDefined = false;
        this->isComplex = false;
    }

    DataTypeInfo(const char* name, unsigned bitWidth, Type *llvmType, unsigned dwarfEnc):
        name(name), bitWidth(bitWidth), llvmType(llvmType), dwarfEnc(dwarfEnc), diType(NULL),
        sl(NULL), isDefined(true), isComplex(false) {};
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

    DataType addDataType(Node* userType, Type* llvmType);

    DataType getType(const string& name, bool createUndefined = false);

    const char *name(unsigned tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].name.c_str();
    }

    const unsigned bitWidth(unsigned tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].bitWidth;
    }

    Type *llvmType(unsigned tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].llvmType;
    }

    DIType *diType(unsigned tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].diType;
    }

    SourceLocation *location(unsigned tid) {
        assert(tid != -1 && "Undefined type");
        return tinfo[tid].sl;
    }

    bool isIntegerDataType(unsigned tid) const {
        return tid >= tint8 && tid <= tint64u;
    }

    bool isSignedDataType(unsigned tid) const {
        return tid >= tint8 && tid <= tint64;
    }

    bool isUnsignedDataType(unsigned tid) const {
        return tid >= tint8u && tid <= tint64u;
    }

    bool isFloatDataType(unsigned tid) const {
	    return tid >= tfloat && tid <= tldouble;
    }

    bool isComplex(unsigned tid) {
        return tinfo[tid].isComplex;
    }

};

// TODO: Replace all places with buildType::name
static string getTypeName(Type *ty) {
	string type_str;
	llvm::raw_string_ostream rso(type_str);
	ty->print(rso);
	return rso.str();
}
