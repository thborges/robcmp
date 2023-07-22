
#pragma once

enum BasicDataType {tvoid, tbool, tchar, tint8, tint16, tint32, tint64, 
  tint8u, tint16u, tint32u, tint64u, tfloat, tdouble, tldouble, tarray,
  /* new types here! */
  __bdt_last};

enum DataQualifier {qnone, qconst, qvolatile};

struct DataTypeInfo {
    const char *name;
    unsigned bitWidth;
    Type *llvmType;
    unsigned dwarfEnc;
    DIType *diType;
};

class BuildTypes {
private:
    map<unsigned, DataTypeInfo> tinfo;
    unsigned nextt = __bdt_last;
public:
    BuildTypes(unsigned targetPointerType) {
        tinfo[tvoid]    = {"void",          0, Type::getVoidTy(global_context),   dwarf::DW_ATE_address};
        tinfo[tbool]    = {"boolean",       1, Type::getInt1Ty(global_context),   dwarf::DW_ATE_boolean};
        tinfo[tchar]    = {"char",          8, Type::getInt8Ty(global_context),   dwarf::DW_ATE_unsigned_char};
        tinfo[tint8]    = {"int8",          8, Type::getInt8Ty(global_context),   dwarf::DW_ATE_signed};
	    tinfo[tint16]   = {"int16",        16, Type::getInt16Ty(global_context),  dwarf::DW_ATE_signed};
        tinfo[tint32]   = {"int32",        32, Type::getInt32Ty(global_context),  dwarf::DW_ATE_signed};
        tinfo[tint64]   = {"int64",        64, Type::getInt64Ty(global_context),  dwarf::DW_ATE_signed};
        tinfo[tint8u]   = {"unsigned8",     8, Type::getInt8Ty(global_context),   dwarf::DW_ATE_unsigned};
        tinfo[tint16u]  = {"unsigned16",   16, Type::getInt16Ty(global_context),  dwarf::DW_ATE_unsigned};
    	tinfo[tint32u]  = {"unsigned32",   32, Type::getInt32Ty(global_context),  dwarf::DW_ATE_unsigned};
        tinfo[tint64u]  = {"unsigned64",   64, Type::getInt64Ty(global_context),  dwarf::DW_ATE_unsigned};
        tinfo[tfloat]   = {"float",        32, Type::getFloatTy(global_context),  dwarf::DW_ATE_float};
        tinfo[tdouble]  = {"double",       64, Type::getDoubleTy(global_context), dwarf::DW_ATE_float};
        tinfo[tldouble] = {"long double", 128, Type::getFP128Ty(global_context),  dwarf::DW_ATE_float};

        unsigned pts = tinfo[targetPointerType].bitWidth;
        Type *pty = tinfo[targetPointerType].llvmType;
        tinfo[tarray]   = {"array", pts, pty, dwarf::DW_ATE_address};

        if (debug_info) {
            for(int t = 0; t < __bdt_last; t++) {
                DataTypeInfo &info = tinfo[t];
                info.diType = DBuilder->createBasicType(info.name, info.bitWidth, info.dwarfEnc);
            }
        }
    }

    unsigned addUserDataType(char *name, unsigned bitWidth, Type* llvmType) {
        DataTypeInfo info;
        info.name = name;
        info.bitWidth = bitWidth;
        info.llvmType = llvmType;
        info.dwarfEnc = dwarf::DW_ATE_address;
        //TODO: info.dwarfEnc = DBuilder->createClassType();
       
        unsigned result = nextt;
        tinfo[nextt++] = info;
        return result;
    }

    const char *name(unsigned tid) {
        return tinfo[tid].name;
    }

    const unsigned bitWidth(unsigned tid) {
        return tinfo[tid].bitWidth;
    }

    unsigned dwarfEnc(unsigned tid) {
        return tinfo[tid].dwarfEnc;
    }

    Type *llvmType(unsigned tid) {
        return tinfo[tid].llvmType;
    }

    DIType *diType(unsigned tid) {
        return tinfo[tid].diType;
    }

    bool isIntegerDataType(unsigned tid) {
        return tid >= tint8 && tid <= tint64u;
    }

    bool isSignedDataType(unsigned tid) {
        return tid >= tint8 && tid <= tint64;
    }

    bool isUnsignedDataType(unsigned tid) {
        return tid >= tint8u && tid <= tint64u;
    }

    bool isFloatDataType(unsigned tid) {
	    return tid >= tfloat && tid <= tldouble;
    }

};
