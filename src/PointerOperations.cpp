#include "PointerOperations.h"

#include "BackLLVM.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"

DataType AddressOf::getDataType() {
    if (dt != BuildTypes::undefinedType || hasSemanticError())
        return dt;

    LoadBase *addressable = dynamic_cast<LoadBase*>(value());
    if (!addressable) {
        yyerrorcpp("The address-of operator requires an addressable expression.", this);
        setSemanticError();
        return BuildTypes::undefinedType;
    }

    if (Load *load = dynamic_cast<Load*>(value())) {
        if (!dynamic_cast<Variable*>(load->getIdentSymbol(false))) {
            yyerrorcpp("The address-of operator requires a variable with storage.", this);
            setSemanticError();
            return BuildTypes::undefinedType;
        }
    }

    DataType valueType = value()->getDataType();
    if (valueType == BuildTypes::undefinedType)
        return valueType;

    dt = buildTypes->getPointerType(valueType, *this, true);
    if (dt == BuildTypes::undefinedType)
        setSemanticError();
    return dt;
}

Value *AddressOf::generate(FunctionImpl *func, BasicBlock *block,
    BasicBlock *allocblock) {
    if (getDataType() == BuildTypes::undefinedType)
        return NULL;

    LoadBase *addressable = dynamic_cast<LoadBase*>(value());
    if (!addressable)
        return NULL;
    addressable->setToStore(true);
    return value()->generateNewBlock(func, &block, allocblock);
}

DataType Dereference::getDataType() {
    if (dt != BuildTypes::undefinedType || hasSemanticError())
        return dt;

    DataType pointerType = pointer()->getDataType();
    if (!buildTypes->isPointer(pointerType)) {
        if (pointerType != BuildTypes::undefinedType) {
            yyerrorcpp(string_format("Can not dereference non-pointer type '%s'.",
                buildTypes->name(pointerType)), this);
        }
        setSemanticError();
        return BuildTypes::undefinedType;
    }

    dt = buildTypes->getPointedType(pointerType);
    return dt;
}

Value *Dereference::generate(FunctionImpl *func, BasicBlock *block,
    BasicBlock *allocblock) {
    DataType valueType = getDataType();
    if (valueType == BuildTypes::undefinedType)
        return NULL;

    Value *address = pointer()->generateNewBlock(func, &block, allocblock);
    if (!address)
        return NULL;
    if (!address->getType()->isPointerTy()) {
        yyerrorcpp("The dereference operand did not produce a pointer value.", this);
        return NULL;
    }
    if (toStore)
        return address;
    if (!block) {
        yyerrorcpp("A pointer can not be dereferenced in a constant global initializer.", this);
        return NULL;
    }

    Builder->SetInsertPoint(block);
    Type *valueLLVMType = buildTypes->llvmType(valueType);
    const DataLayout &layout = mainmodule->getDataLayout();
    Align align = layout.getABITypeAlign(valueLLVMType);
    return Builder->CreateAlignedLoad(valueLLVMType, address, align, false, "deref");
}

DataType PointerStore::getDataType() {
    if (dt != BuildTypes::undefinedType || hasSemanticError())
        return dt;

    DataType pointerType = pointer()->getDataType();
    if (!buildTypes->isPointer(pointerType)) {
        if (pointerType != BuildTypes::undefinedType) {
            yyerrorcpp(string_format("Can not store through non-pointer type '%s'.",
                buildTypes->name(pointerType)), this);
        }
        setSemanticError();
        return BuildTypes::undefinedType;
    }
    dt = buildTypes->getPointedType(pointerType);
    return dt;
}

Value *PointerStore::generate(FunctionImpl *func, BasicBlock *block,
    BasicBlock *allocblock) {
    DataType valueType = getDataType();
    if (valueType == BuildTypes::undefinedType)
        return NULL;

    Value *address = pointer()->generateNewBlock(func, &block, allocblock);
    Value *storedValue = value()->generateNewBlock(func, &block, allocblock);
    if (!address || !storedValue)
        return NULL;
    if (!address->getType()->isPointerTy()) {
        yyerrorcpp("The store operand did not produce a pointer value.", this);
        return NULL;
    }

    Builder->SetInsertPoint(block);
    Type *valueLLVMType = buildTypes->llvmType(valueType);
    const DataLayout &layout = mainmodule->getDataLayout();
    Align align = layout.getABITypeAlign(valueLLVMType);
    return Builder->CreateAlignedStore(storedValue, address, align, false);
}

Value *NullPointer::generate(FunctionImpl *, BasicBlock *, BasicBlock *) {
    if (!buildTypes->isPointer(dt)) {
        yyerrorcpp("Internal error: null value does not have a pointer type.", this);
        return NULL;
    }
    PointerType *pointerType = dyn_cast<PointerType>(buildTypes->llvmType(dt));
    if (!pointerType) {
        yyerrorcpp("Internal error: pointer type has no LLVM pointer representation.", this);
        return NULL;
    }
    return ConstantPointerNull::get(pointerType);
}
