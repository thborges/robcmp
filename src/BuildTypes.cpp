
#include "BuildTypes.h"
#include "Node.h"
#include "Variable.h"

BuildTypes::BuildTypes(DataType targetPointerType) {
    tinfo[tvoid]    = {"void",          0, Type::getVoidTy(global_context),    dwarf::DW_ATE_address};
    tinfo[tbool]    = {"bool",          1, Type::getInt1Ty(global_context),    dwarf::DW_ATE_boolean};
    tinfo[tchar]    = {"char",          8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_unsigned_char};
    tinfo[tint2]    = {"int2",          2, Type::getIntNTy(global_context, 2), dwarf::DW_ATE_signed};
    tinfo[tint8]    = {"int8",          8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_signed};
    tinfo[tint16]   = {"int16",        16, Type::getInt16Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint32]   = {"int32",        32, Type::getInt32Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint64]   = {"int64",        64, Type::getInt64Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint8u]   = {"unsigned8",     8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_unsigned};
    tinfo[tint16u]  = {"unsigned16",   16, Type::getInt16Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tint32u]  = {"unsigned32",   32, Type::getInt32Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tint64u]  = {"unsigned64",   64, Type::getInt64Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tfloat]   = {"float",        32, Type::getFloatTy(global_context),   dwarf::DW_ATE_float};
    tinfo[tdouble]  = {"double",       64, Type::getDoubleTy(global_context),  dwarf::DW_ATE_float};
    tinfo[tldouble] = {"long double", 128, Type::getFP128Ty(global_context),   dwarf::DW_ATE_float};

    unsigned pts = tinfo[targetPointerType].bitWidth;
    Type *pty = tinfo[targetPointerType].llvmType;
    tinfo[tarray]   = {"array", pts, pty, dwarf::DW_ATE_address};

    const DataLayout &dl = mainmodule->getDataLayout();
    for(int t = 0; t < __bdt_last; t++) {
        DataTypeInfo &info = tinfo[t];
        namedTypes[info.name] = t;
        if (debug_info) {
            unsigned bitWidth = 0;
            if (t > 0) // no void
                bitWidth = dl.getTypeAllocSizeInBits(info.llvmType);
            info.diType = DBuilder->createBasicType(info.name, bitWidth, info.dwarfEnc);
        }
    }
}

DataType BuildTypes::getType(const string& name, bool createUndefined) {
    auto ut = namedTypes.find(name);
    if (ut == namedTypes.end()) {
        if (createUndefined)
            return addDataType(DataTypeInfo(name));
    } else if (tinfo[ut->second].isDefined) {
        return ut->second;
    }
    return undefinedType;
}

DataType BuildTypes::addDataType(Node* userType, Type* llvmType) {
    const string& name = userType->getName();
    auto udt = namedTypes.find(name);
    DataType id;

    const DataLayout &dl = mainmodule->getDataLayout();
    uint64_t bitWidth = dl.getTypeAllocSizeInBits(llvmType);
    uint32_t align = dl.getABITypeAlign(llvmType).value();
    
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
    info.isComplex = true;
    info.dwarfEnc = 0;
    
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
            RobDbgInfo.currFile(), userType->getLineNo(), bitWidth, align, 0,
            DINode::DIFlags::FlagZero, nullptr, dielems);
    }
    return id;
}
