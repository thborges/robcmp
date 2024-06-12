
#include "BuildTypes.h"
#include "HeaderGlobals.h"
#include "Node.h"
#include "Scanner.h"
#include "Variable.h"
#include "BackLLVM.h"

BuildTypes::BuildTypes(DataType targetPointerType) {
    tinfo[tvoid]    = {"void",          0, Type::getVoidTy(global_context),    dwarf::DW_ATE_address};
    tinfo[tbool]    = {"bool",          1, Type::getInt1Ty(global_context),    dwarf::DW_ATE_boolean};
    tinfo[tchar]    = {"char",          8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_unsigned_char};
    tinfo[tint2]    = {"int2",          2, Type::getIntNTy(global_context, 2), dwarf::DW_ATE_signed};
    tinfo[tint3]    = {"int3",          3, Type::getIntNTy(global_context, 3), dwarf::DW_ATE_signed};
    tinfo[tint4]    = {"int4",          4, Type::getIntNTy(global_context, 4), dwarf::DW_ATE_signed};
    tinfo[tint5]    = {"int5",          5, Type::getIntNTy(global_context, 5), dwarf::DW_ATE_signed};
    tinfo[tint6]    = {"int6",          6, Type::getIntNTy(global_context, 6), dwarf::DW_ATE_signed};
    tinfo[tint7]    = {"int7",          7, Type::getIntNTy(global_context, 7), dwarf::DW_ATE_signed};
    tinfo[tint8]    = {"int8",          8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_signed};
    tinfo[tint16]   = {"int16",        16, Type::getInt16Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint32]   = {"int32",        32, Type::getInt32Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint64]   = {"int64",        64, Type::getInt64Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint8u]   = {"uint8",         8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_unsigned};
    tinfo[tint16u]  = {"uint16",       16, Type::getInt16Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tint32u]  = {"uint32",       32, Type::getInt32Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tint64u]  = {"uint64",       64, Type::getInt64Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tfloat]   = {"float",        32, Type::getFloatTy(global_context),   dwarf::DW_ATE_float};
    tinfo[tdouble]  = {"double",       64, Type::getDoubleTy(global_context),  dwarf::DW_ATE_float};
    tinfo[tldouble] = {"long double", 128, Type::getFP128Ty(global_context),   dwarf::DW_ATE_float};

    unsigned pts = tinfo[targetPointerType].bitWidth;

    const DataLayout &dl = mainmodule->getDataLayout();
    for(int t = 0; t < __bdt_last; t++) {
        DataTypeInfo &info = tinfo[t];
        namedTypes[info.name] = t;
        if (debug_info) {
            unsigned bitWidth = 0;
            if (t > 0) // no void
                bitWidth = dl.getTypeAllocSizeInBits(info.llvmType);
            info.diType = DBuilder->createBasicType(info.name, bitWidth, info.dwarfEnc);
            info.diPointerType = DBuilder->createPointerType(info.diType, pts);
        }
    }
}

DataType BuildTypes::getArrayType(const string& elementName, SourceLocation n, 
    unsigned char dimensions, bool createUndefined) {
        
    string arrayTyName = elementName;
    for(int i = 0; i < dimensions; i++)
        arrayTyName += "[]";

    auto ut = namedTypes.find(arrayTyName);
    if (ut == namedTypes.end()) {
        if (createUndefined) {
            auto elementTyIter = namedTypes.find(elementName);
            auto elementInfo = tinfo[elementTyIter->second];
            if (elementTyIter == namedTypes.end() || elementInfo.llvmType == NULL) {
                yyerrorcpp(string_format("Type %s is not defined.", 
                    elementName.c_str()), &n, true);
            } else {
                DataType dt = addDataType(DataTypeInfo(arrayTyName));
                DataTypeInfo &info = tinfo[dt];
                info.llvmType = ArrayType::get(elementInfo.llvmType, 0); // we couldn't know the array size at compile time
                info.isDefined = true;
                info.isComplex = false;
                info.arrayDimensions = dimensions;
                info.bitWidth = elementInfo.bitWidth;
                info.dwarfEnc = dwarf::DW_ATE_address;
                if (debug_info) {
                    info.diType = DBuilder->createArrayType(0, 0, elementInfo.diType, {});
                    unsigned ptbw = tinfo[currentTarget().pointerType].bitWidth;
                    info.diPointerType = DBuilder->createPointerType(elementInfo.diType, ptbw);
                }
                return dt;
            }
        }
    } else if (tinfo[ut->second].isDefined || createUndefined) {
        return ut->second;
    }
    return undefinedType;
}

DataType BuildTypes::getArrayElementType(DataType arrayDt) {
    assert(isArrayOrMatrix(arrayDt) && "arrayDt must be an array or matrix.");
    string elementName = name(arrayDt);
    elementName = elementName.substr(0, elementName.length() - 2*dimensions(arrayDt));
    return getType(elementName);
}

DataType BuildTypes::getType(const string& name, bool createUndefined) {
    auto ut = namedTypes.find(name);
    if (ut == namedTypes.end()) {
        if (createUndefined) {
            DataTypeInfo dti(name);
            dti.isComplex = true;
            return addDataType(dti);
        }
    } else /*if (tinfo[ut->second].isDefined || createUndefined)*/ {
        return ut->second;
    }
    return undefinedType;
}

DataType BuildTypes::addDataType(Node* userType, Type* llvmType, unsigned typeBitWidth,
    bool isEnum) {
    const string& name = userType->getName();
    auto udt = namedTypes.find(name);
    DataType id;

    const DataLayout &dl = mainmodule->getDataLayout();

    uint64_t bitWidth = typeBitWidth;
    if (typeBitWidth == 0 && llvmType->isSized())
        typeBitWidth = dl.getTypeAllocSizeInBits(llvmType);
    
    if (udt == namedTypes.end()) {
        DataTypeInfo info(name.c_str(), bitWidth, llvmType, 0);
        id = addDataType(info);
    } else {
        id = udt->second;
    }
    DataTypeInfo &info = tinfo[id];
    info.sl = userType;
    info.llvmType = llvmType;
    info.isDefined = true;
    info.isComplex = !isEnum;
    info.isEnum = isEnum;
    info.dwarfEnc = 0;
    info.bitWidth = bitWidth;
    info.isInternal = false;
    info.isInterface = false;
    
    if (debug_info) {
        unsigned offset = 0;
        vector<llvm::Metadata *> elems;
        vector<Node*> members;
        for(auto& [key, m] : userType->getSymbols()) {
            if (Node *n = dynamic_cast<Variable*>(m))
                members.push_back(n);
        }

        assert((members.size() == llvmType->getNumContainedTypes()) &&
            "Number of fields differ between LLVM Type and Node.");
        
        int i = 0;
        elems.reserve(members.size());
        for(Node *m : members) {
            DataType mdt = m->getDataType();
            if (mdt == -1 || tinfo[mdt].bitWidth == 0) {
                continue;
            }
            Type *memberTy = llvmType->getContainedType(i);
            uint64_t memberBitWidth = dl.getTypeSizeInBits(memberTy);
            uint32_t memberAlign = dl.getABITypeAlign(memberTy).value();
            DIType *di = DBuilder->createMemberType(RobDbgInfo.currScope(), m->getName(), 
                RobDbgInfo.currFile(), m->getLineNo(), 
                memberBitWidth, memberAlign, offset, DINode::DIFlags::FlagZero,
                diType(m->getDataType()));
            elems.push_back(di);
            offset += memberBitWidth;
            i++;
        }
        auto dielems = DBuilder->getOrCreateArray(elems);
        info.diType = DBuilder->createClassType(RobDbgInfo.currScope(), name,
            RobDbgInfo.currFile(), userType->getLineNo(), bitWidth, 1, 0,
            DINode::DIFlags::FlagZero, nullptr, dielems);
        unsigned ptbw = tinfo[currentTarget().pointerType].bitWidth;
        info.diPointerType = DBuilder->createPointerType(info.diType, ptbw);
    }
    return id;
}

Type *BuildTypes::llvmType(DataType tid) {
    if (tid == -1)
        return NULL;
    else
        return tinfo[tid].llvmType;
}
