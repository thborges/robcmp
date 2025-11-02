
#include "FieldAccess.h"
#include "Pointer.h"
#include "UserType.h"
#include "NamedConst.h"

Value* FieldAccess::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    // getDataType, if not queried yet
    getDataType();

    Value *alloc = leftValue->generateNewBlock(func, &block, allocblock);

    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);

    loadSymbol = leftValue->getLoadSymbol();
    if (Pointer *reg = dynamic_cast<Pointer*>(loadSymbol)) {
        if (toStore) {
            return alloc;
        }

        /* For pointers (aka. registers) get the requested bit value through bit shifting
           This code does:
            *   v = symbol->value << pointerbits - field_start - field_width
            *   v = v >> pointer_bits - field_width
            */

        // Load reg value (received a ptr)
        Type *req_eq_ty = Type::getIntNTy(global_context, buildTypes->bitWidth(reg->getDataType()));
        alloc = Builder->CreateLoad(req_eq_ty, alloc, loadSymbol->hasQualifier(qvolatile), field);

        // Extract field value from reg
        Node *member = loadSymbol->findMember(field);
        assert(member && "Member not found.");
        int bs = buildTypes->bitWidth(reg->getDataType()) - buildTypes->bitWidth(member->getDataType());
        unsigned fieldStartBit = reg->getFieldStartBit(field);
        if (bs - fieldStartBit > 0)
            alloc = Builder->CreateShl(alloc, ConstantInt::get(req_eq_ty, bs - fieldStartBit));
        if (bs > 0)
            alloc = Builder->CreateLShr(alloc, ConstantInt::get(req_eq_ty, bs));
        return Builder->CreateTrunc(alloc, buildTypes->llvmType(dt));

    } 
    
    DataType leftDt = leftValue->getDataType();
    if (buildTypes->isComplex(leftDt)) {
        // Find the field of the complex type
        Node *userTypeNode = findSymbol(buildTypes->name(leftDt));
        UserType *userType = dynamic_cast<UserType*>(userTypeNode);
        Node *fieldNode = userType->findMember(field);

        if (fieldNode->isConstExpr())
            return fieldNode->generate(NULL, NULL, NULL);
        else {
            loadSymbol = dynamic_cast<Variable*>(fieldNode);
            assert(loadSymbol && "field must be a variable.");

            int gepidx = loadSymbol->getGEPIndex();
            Value *gep = Builder->CreateStructGEP(buildTypes->llvmType(leftDt), alloc, gepidx, field);
            if (toStore || buildTypes->isComplex(dt) || buildTypes->isArrayOrMatrix(dt)) {
                return gep;
            } else {
                Type *fieldTy = buildTypes->llvmType(dt);
                return Builder->CreateLoad(fieldTy, gep, field);
            }
        }

    } else {
        Node *fieldOrConst = leftValue->findMember(field);
        if (Variable *pseudoVar = dynamic_cast<Variable*>(fieldOrConst)) {
            // pseudo vars .size, .rows and .cols for array and matrices
            Value *value = pseudoVar->getAlloc();
            Type *fieldTy = buildTypes->llvmType(pseudoVar->getDataType());
            return Builder->CreateLoad(fieldTy, value, field);

        } else if (NamedConst *namedConst = dynamic_cast<NamedConst*>(fieldOrConst)) {
            return namedConst->generate(NULL, NULL, NULL);
        }

        yyerrorcpp(string_format("Field access (%s) in a non-complex type (%s).",
            field.c_str(), buildTypes->name(leftValue->getDataType())), this);
        return NULL;
    }
}

DataType FieldAccess::getDataType() {
    if (dt == BuildTypes::undefinedType)
        dt = leftValue->findMember(field)->getDataType();
    return dt;
}
