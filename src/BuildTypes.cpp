
#include "BuildTypes.h"
#include "HeaderGlobals.h"
#include "Identifier.h"
#include "NamedConst.h"
#include "Node.h"
#include "Program.h"
#include "Scanner.h"
#include "Variable.h"
#include "Array.h"
#include "Matrix.h"
#include "UserType.h"
#include "BackLLVM.h"
#include "Int8.h"

BuildTypes::BuildTypes(DataType targetPointerType) : 
    targetPointerType(targetPointerType) {

    tinfo[tvoid]    = {"void",          0, Type::getVoidTy(global_context),    dwarf::DW_ATE_address};
    tinfo[tbool]    = {"bool",          1, Type::getInt1Ty(global_context),    dwarf::DW_ATE_boolean};
    tinfo[tchar]    = {"char",          8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_unsigned_char};
    tinfo[tint8]    = {"int8",          8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_signed};
    tinfo[tint16]   = {"int16",        16, Type::getInt16Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint32]   = {"int32",        32, Type::getInt32Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint64]   = {"int64",        64, Type::getInt64Ty(global_context),   dwarf::DW_ATE_signed};
    tinfo[tint2u]   = {"uint2",         2, Type::getIntNTy(global_context, 2), dwarf::DW_ATE_unsigned};
    tinfo[tint3u]   = {"uint3",         3, Type::getIntNTy(global_context, 3), dwarf::DW_ATE_unsigned};
    tinfo[tint4u]   = {"uint4",         4, Type::getIntNTy(global_context, 4), dwarf::DW_ATE_unsigned};
    tinfo[tint5u]   = {"uint5",         5, Type::getIntNTy(global_context, 5), dwarf::DW_ATE_unsigned};
    tinfo[tint6u]   = {"uint6",         6, Type::getIntNTy(global_context, 6), dwarf::DW_ATE_unsigned};
    tinfo[tint7u]   = {"uint7",         7, Type::getIntNTy(global_context, 7), dwarf::DW_ATE_unsigned};
    tinfo[tint8u]   = {"uint8",         8, Type::getInt8Ty(global_context),    dwarf::DW_ATE_unsigned};
    tinfo[tint12u]  = {"uint12",       12, Type::getIntNTy(global_context, 12),dwarf::DW_ATE_unsigned};
    tinfo[tint16u]  = {"uint16",       16, Type::getInt16Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tint32u]  = {"uint32",       32, Type::getInt32Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tint64u]  = {"uint64",       64, Type::getInt64Ty(global_context),   dwarf::DW_ATE_unsigned};
    tinfo[tfloat]   = {"float",        32, Type::getFloatTy(global_context),   dwarf::DW_ATE_float};
    tinfo[tdouble]  = {"double",       64, Type::getDoubleTy(global_context),  dwarf::DW_ATE_float};
    tinfo[tldouble] = {"ldouble",     128, Type::getFP128Ty(global_context),   dwarf::DW_ATE_float};

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
    } else {
        return ut->second;
    }
    return undefinedType;
}

DataType BuildTypes::addDataType(Node* userType, Type* llvmType, unsigned typeBitWidth,
    bool isEnum) {
    string name = userType->getName();
    if (UserType *ut = dynamic_cast<UserType*>(userType))
        name = ut->getTypeName();
    auto udt = namedTypes.find(name);
    DataType id;

    const DataLayout& dl = mainmodule->getDataLayout();
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
    return id;
}

Type *BuildTypes::llvmType(DataType tid) {
    if (tid == -1)
        return NULL;
    else
        return tinfo[tid].llvmType;
}

void BuildTypes::generateDebugInfoForEnum(DataTypeInfo &info, Node *userType) {
    
    unsigned offset = 0;
    vector<llvm::Metadata *> elems;

    for(auto *m : userType->children()) {
        if (NamedConst *n = dynamic_cast<NamedConst*>(m)) {
            Node *value = n->getValue();
            uint8_t v = 0;
            if (Int8 *i8 = dynamic_cast<Int8*>(value))
                v = i8->getNumber();
            else if (UInt8 *ui8 = dynamic_cast<UInt8*>(value))
                v = ui8->getNumber();
            else
                assert(0 && "Unknown enum value node.");

            auto etor = DBuilder->createEnumerator(n->getName(), v);
            elems.push_back(etor);
        } else
            assert(0 && "Unknown enum node.");
    }

    auto dielems = DBuilder->getOrCreateArray(elems);
    info.diType = DBuilder->createEnumerationType(RobDbgInfo.currScope(), info.name,
        RobDbgInfo.currFile(), userType->getLineNo(), info.bitWidth, 1,
        dielems, tinfo[tint8].diType);
}

void BuildTypes::generateDebugInfoForUserType(DataTypeInfo &info, Node *userType) {
    
    const DataLayout& dl = mainmodule->getDataLayout();
    unsigned offset = 0;
    vector<llvm::Metadata *> elems;
    vector<Node*> members;
    for(auto *m : userType->children()) {
        if (Node *n = dynamic_cast<Variable*>(m))
            members.push_back(n);
    }

    //assert((members.size() == llvmType->getNumContainedTypes()) &&
    //    "Number of fields differ between LLVM Type and Node.");
    
    elems.reserve(members.size());
    for(Node *m : members) {
        DataType mdt = m->getDataType();
        if (isInterface(mdt)) {
            // search the injections
            string fieldName = info.name;
            fieldName.append("." + m->getName());
            if (injections.find(fieldName) != injections.end()) {
                string injType = injections[fieldName].first;
                Node *symbol = Identifier(injType, userType->getLoc()).getSymbol(program, false);
                if (symbol)
                    mdt = symbol->getDataType();
            }
        }
        if (mdt == -1 || tinfo[mdt].bitWidth == 0) {
            continue;
        }
        
        Type *memberTy = tinfo[mdt].llvmType;
        DIType *memberDiType = diType(mdt);
        if (Variable *v = dynamic_cast<Variable*>(m)) {
            if (v->getPointerMode() == pm_pointer) {
                memberTy = memberTy->getPointerTo();
                memberDiType = diPointerType(mdt);
                if (!memberDiType) {
                    // parent field 
                    memberDiType = diPointerType(targetPointerType);
                }
            }
        }
        
        uint64_t memberBitWidth = dl.getTypeAllocSizeInBits(memberTy);
        if (memberTy->isArrayTy()) {
            memberBitWidth = dl.getTypeAllocSizeInBits(memberTy->getArrayElementType());
            if (Matrix *matrix = dynamic_cast<Matrix*>(m))
                memberBitWidth *= matrix->getRows() * matrix->getCols();
            else if (Array *array = dynamic_cast<Array*>(m))
                memberBitWidth *= array->getSize();
        }
        uint32_t memberAlignInBits = dl.getABITypeAlign(memberTy).value() * 8;
        
        // align offset according to memberAlign
        // TODO: improved this when implementing packed structs/types
        if (offset % memberAlignInBits != 0)
            offset += memberAlignInBits - (offset % memberAlignInBits);

        DIType *di = DBuilder->createMemberType(RobDbgInfo.currScope(), m->getName(), 
            RobDbgInfo.currFile(), m->getLineNo(), memberBitWidth, memberAlignInBits,
            offset, DINode::DIFlags::FlagZero, memberDiType);
        assert(di);
        elems.push_back(di);
        offset += memberBitWidth;
    }

    auto dielems = DBuilder->getOrCreateArray(elems);
    info.diType = DBuilder->createClassType(RobDbgInfo.currScope(), info.name,
        RobDbgInfo.currFile(), userType->getLineNo(), info.bitWidth, 1, 0,
        DINode::DIFlags::FlagZero, nullptr, dielems);
    unsigned ptbw = tinfo[targetPointerType].bitWidth;
    info.diPointerType = DBuilder->createPointerType(info.diType, ptbw);
}

void BuildTypes::generateDebugInfoForTypes() {
    if (!debug_info)
        return;

    for (DataType dt = nextt-1; dt >= __bdt_last; dt--) {
        auto& info = tinfo[dt];

        Node *userType = program->findSymbol(info.name);
        if (!userType)
            continue;

        if (info.isEnum)
            generateDebugInfoForEnum(info, userType);
        else
            generateDebugInfoForUserType(info, userType);
    }
}

bool BuildTypes::isArrayCompatible(DataType srcDt, DataType destDt) {
    if (isArray(srcDt) ^ isArray(destDt))
        return false;
    if (tinfo[srcDt].arrayDimensions != tinfo[destDt].arrayDimensions)
        return false;
    DataType elSrc = getArrayElementType(srcDt);
    DataType elDest = getArrayElementType(destDt);
    if (elSrc != elDest) {
        if ((elSrc == tint8 || elSrc == tint8u || elSrc == tchar) && 
            (elDest == tint8 || elDest == tint8u || elDest == tchar)) {
            return true;
        }
    }
    return true;
}