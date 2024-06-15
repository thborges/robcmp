
#include "PropagateTypes.h"
#include "ConstructorCall.h"

void PropagateTypes::propagateChildren(Node& n, std::function<void(Node&)> lambda) {
    for (auto it = n.node_children.begin(); it != n.node_children.end(); ++it) {
        Node *replace = (*it)->accept(*this);
        if (replace) {
            *it = replace;
        }
        if (lambda)
            lambda(**it);
    }
}

Node* PropagateTypes::coerceTo(Node *n, const DataType destTy, bool warns) {
    if (isUndefined(n))
        return NULL;
    DataType valueTy = n->getDataType();

    // can coerce only between numeric types
    bool lIsNumeric = buildTypes->isNumericDataType(destTy);
    bool rIsNumeric = buildTypes->isNumericDataType(valueTy);
    if (!lIsNumeric || !rIsNumeric) {
        yyerrorcpp(string_format("Can not cast from '%s' to '%s'.",
            buildTypes->name(valueTy),
            buildTypes->name(destTy)), n);
        return NULL;
    }

    bool destUnsigned = buildTypes->isUnsignedDataType(destTy);
    bool valueUnsigned = buildTypes->isUnsignedDataType(valueTy);
    uint destBWidth = buildTypes->bitWidth(destTy);
    uint valueBWidth = buildTypes->bitWidth(valueTy);

    // both sides integer
    if (buildTypes->isIntegerDataType(destTy) && buildTypes->isIntegerDataType(valueTy)) {
        
        // if we have signed and unsigned operands, convert valueTy to destTy
        if (warns) {
            if ((destUnsigned ^ valueUnsigned) && valueTy != tbool) {
                // if value is constant, convert it to the dest type
                bool valueIsConstant = n->isConstExpr();
                if (valueIsConstant) {
                    valueTy = valueUnsigned ? buildTypes->unsignedToSigned(valueTy) : 
                        buildTypes->signedToUnsigned(valueTy);
                } else {
                    string name = n->getName();
                    if (name == "")
                        name = "Value";
                    if (destUnsigned)
                        yywarncpp(string_format("%s has been used as unsigned.", name.c_str()), n);
                    else
                        yywarncpp(string_format("%s has been used as signed.", name.c_str()), n);
                }
            }
        }

        // if destTy is larger, SExtended or ZExtended value
        if (destBWidth > valueBWidth) {
            Node *expand;
            if (destUnsigned)
                expand = new ZExtInt(n, destTy);
            else
                expand = new SExtInt(n, destTy);
            return expand;

        } else if (destBWidth < valueBWidth) {
            if (warns) {
                string name = n->getName();
                if (name == "")
                    name = "Value";
                yywarncpp(string_format("%s (%s) has been truncated to fit %s.", name.c_str(), 
                    buildTypes->name(valueTy), buildTypes->name(destTy)), n);
            }
            return new TruncInt(n, destTy);
        }
    }

    // both sides float point
    if (buildTypes->isFloatDataType(destTy) && buildTypes->isFloatDataType(valueTy)) {
        
        // if destTy is larger, Extended value
        if (destBWidth > valueBWidth)
            return new ExtendFloat(n, destTy);
        else if (destBWidth < valueBWidth) {
            if (warns)
                yywarncpp(string_format("Value has been truncated to %s.", buildTypes->name(destTy)), n);
            return new TruncFloat(n, destTy);
        }
    }

    bool isDestInteger = buildTypes->isIntegerDataType(destTy);
    bool isDestFloat = buildTypes->isFloatDataType(destTy);
    bool isValueInteger = buildTypes->isIntegerDataType(valueTy);
    bool isValueFloat = buildTypes->isFloatDataType(valueTy);
    
    if (isDestInteger && isValueFloat) {
        if (warns)
            yywarncpp(string_format("Float value has been truncated to %s.", buildTypes->name(destTy)), n);
        return new FloatToInt(n, destTy);
    } else if (isValueInteger && isDestFloat) {
        return new IntToFloat(n, destTy);
    }

    return n;
}

Value *ForcedCast::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);
    Node *converted = PropagateTypes::coerceTo(node, dt, false);
    if (converted)
        return converted->generate(func, block, allocblock);
    else
        return NULL;
};

DataType PropagateTypes::coerceArithOrCmp(Node &n, Node *lNode, Node *rNode) {
    DataType returnTy = BuildTypes::undefinedType;

    if (isUndefined(lNode) || isUndefined(rNode)) {
        n.setSemanticError();
        return returnTy;
    }

    DataType lTy = lNode->getDataType();
    DataType rTy = rNode->getDataType();

    // binary operations only between numeric types
    bool lIsNumeric = buildTypes->isNumericDataType(lTy);
    bool rIsNumeric = buildTypes->isNumericDataType(rTy);
    if (!lIsNumeric || !rIsNumeric) {
        yyerrorcpp("Non-numeric types are not supported by this operator.", &n);
        return returnTy;
    }

    uint lBWidth = buildTypes->bitWidth(lTy);
    uint rBWidth = buildTypes->bitWidth(rTy);

    // both sides integer
    if (buildTypes->isIntegerDataType(lTy) && buildTypes->isIntegerDataType(rTy)) {
        
        bool lUnsigned = buildTypes->isUnsignedDataType(lTy);
        bool rUnsigned = buildTypes->isUnsignedDataType(rTy);

        // if we have signed and unsigned operands
        if (lUnsigned ^ rUnsigned) {
            // if one side is constant, convert it to the other side type
            bool lIsConstant = lNode->isConstExpr();
            bool rIsConstant = rNode->isConstExpr();
            if (lIsConstant ^ rIsConstant) {
                if (lIsConstant) {
                    lTy = lUnsigned ? buildTypes->unsignedToSigned(lTy) : buildTypes->signedToUnsigned(lTy);
                    returnTy = rTy;
                } else {
                    rTy = rUnsigned ? buildTypes->unsignedToSigned(rTy) : buildTypes->signedToUnsigned(rTy);
                    returnTy = lTy;
                }
                    
            } else {
                yywarncpp("The unsigned operand was converted to signed.", &n);
                if (lUnsigned)
                    lTy = buildTypes->unsignedToSigned(lTy);
                else
                    rTy = buildTypes->unsignedToSigned(rTy);
            }
        }

        // At this point, rTy has the same signedness of lTy.
        // Thus, temporarily set returnTy to check the signedness below
        returnTy = rTy;

        // if sizes are distinct, the smaller int is SExtended or ZExtended
        if (lBWidth != rBWidth) {
            Node *convert = lBWidth < rBWidth ? lNode : rNode;
            DataType newTy = lBWidth < rBWidth ? rTy : lTy;
            Node *expand;
            if (buildTypes->isSignedDataType(returnTy))
                expand = new SExtInt(convert, newTy);
            else
                expand = new ZExtInt(convert, newTy);
            n.node_children[lBWidth < rBWidth ? 0 : 1] = expand;
            return newTy;
        }
    }

    // both sides float point
    if (buildTypes->isFloatDataType(lTy) && buildTypes->isFloatDataType(rTy)) {
        
        // if sizes are distinct, the smaller float is extended
        if (lBWidth != rBWidth) {
            Node *convert = lBWidth < rBWidth ? lNode : rNode;
            DataType newTy = lBWidth < rBWidth ? rTy : lTy;
            ExpandFloat *ef = new ExpandFloat(convert, newTy);
            n.node_children[lBWidth < rBWidth ? 0 : 1] = ef;
            return newTy;
        }
    }

    // one side float and other side int
    bool lIsInteger = buildTypes->isIntegerDataType(lTy);
    bool lIsFloat = buildTypes->isFloatDataType(lTy);
    bool rIsInteger = buildTypes->isIntegerDataType(rTy);
    bool rIsFloat = buildTypes->isFloatDataType(rTy);
    if (lIsInteger && rIsFloat || lIsFloat && rIsInteger) {
        Node *convert = lIsInteger ? new IntToFloat(lNode, rTy) : new IntToFloat(rNode, lTy);
        n.node_children[lIsInteger ? 0 : 1] = convert;
        DataType newTy = lIsInteger ? rTy : lTy;
        return newTy;
    }

    if ((lTy == tchar && rTy == tint8u) || (lTy == tint8u && rTy == tchar))
        return lTy;
    else if (lTy == rTy) {
        return lTy;
    } else {
        yyerrorcpp(string_format("FIXME: the pair %s and %s needs a coercion.", 
            buildTypes->name(lTy), buildTypes->name(rTy)), &n);
        assert(returnTy != BuildTypes::undefinedType);
    }

    return returnTy;
}

Node* PropagateTypes::visit(BinaryOp& n) {
    propagateChildren(n);
    n.dt = coerceArithOrCmp(n, n.lhsn(), n.rhsn());    
    return NULL;
}

Node* PropagateTypes::visit(CmpOp& n) {
    propagateChildren(n);
    coerceArithOrCmp(n, n.lexpn(), n.rexpn());
    return NULL;
}

Node* PropagateTypes::visit(FunctionImpl& n) {
    currentFunctionDt = n.getDataType();
    propagateChildren(n);
    currentFunctionDt = BuildTypes::undefinedType;
    return NULL;
}

Node* PropagateTypes::visit(Return& n) {
    if (!n.value()){
        n.dt = tvoid;
        return NULL;
    } else {
        propagateChildren(n);
        DataType valueDt = n.value()->getDataType();
        if (currentFunctionDt != valueDt) {
            Node *converted = coerceTo(n.node_children[0], currentFunctionDt);
            if (converted) {
                n.node_children[0] = converted;
                n.dt = converted->dt;
            }
        } else {
            if (buildTypes->isComplex(valueDt)) {
                // defer the pointer before returning
                n.node_children[0] = new DeferPointer(n.value());
            }
            n.dt = valueDt;
        }
    }
    return NULL;
}

Node* PropagateTypes::visit(FunctionCall& fc) {
    propagateChildren(fc);
    
    // if the function name is the name of a primitive or complex type,
    // replace the function call node by a more specific one
    DataType dt = buildTypes->getType(fc.getName());
    
    // if the function name is a UserType, its DataType is not created yet.
    // Thus, we call findSymbol and getDataType to create it
    if (dt == BuildTypes::undefinedType) {
        Identifier typeName(fc.getName(), fc.getLoc());
        Node *symbol = typeName.getSymbol(&fc, false);
        if (dynamic_cast<UserType*>(symbol))
            dt = symbol->getDataType();
    }

    if (dt != BuildTypes::undefinedType) {

        // if dt is the name of a primitive type and the call has only one
        // argument, replace the function call node to a Cast one
        unsigned p = fc.getParameters().size();
        if (buildTypes->isPrimitiveType(dt) && p == 1) {
            Node *param = fc.getParameters()[0];
            ForcedCast *cast = new ForcedCast(param, dt);
            return cast;
        } 
    
        // if dt is the name of a complex type and the call has no argument,
        // replace the function call node to a ConstructorCall one
        if (buildTypes->isComplex(dt) && p == 0) {
            ConstructorCall *constructor = new ConstructorCall(fc.getName(), fc.getLoc());
            constructor->setScope(fc.getScope());
            return constructor;
        }
    }

    // coerce call arguments
    Identifier calledIdent(fc.getName(), fc.getLoc());
    Node *calledSymbol = calledIdent.getSymbol(&fc, false);
    FunctionBase *calledFunc = dynamic_cast<FunctionBase*>(calledSymbol);
    if (calledFunc && calledFunc->getNumCodedParams() == fc.getParameters().size()) {
        auto calledFuncParam = calledFunc->getParameters().getParameters().begin();
        auto passedParam = fc.getParameters().begin();
        while (passedParam != fc.getParameters().end()) {
            DataType call_dt = (*passedParam)->getDataType();
            DataType def_dt = (*calledFuncParam)->getDataType();
            if (buildTypes->isPrimitiveType(def_dt) && call_dt != def_dt) {
                Node *newParam = coerceTo((*passedParam), def_dt);
                *passedParam = newParam;
            }
            calledFuncParam++;
            passedParam++;
        }
    }

    return NULL;
}

Node* PropagateTypes::visit(Matrix& n) {
    // visit elements to propagate their types
    for(MatrixElement *me : n.getElements()) {
        for(ArrayElement *k: me->array->getElements()) {
            Node *aux = k->value->accept(*this);
            if (aux)
                k->value = aux;
        }
    }

    // find the matrix and elements type
    n.dt = n.getDataType();
    DataType edt = n.getElementDataType();

    // visit elements to sext or zext their values
    for(MatrixElement *me : n.getElements()) {
        for(ArrayElement *k: me->array->getElements()) {
            k->value = coerceTo(k->value, edt);
        }
    }

    return NULL;
}

Node* PropagateTypes::visit(Array& n) {
    // visit elements to propagate their types
    for(ArrayElement *ae : n.getElements()) {
        Node *aux = ae->value->accept(*this);
        if (aux)
            ae->value = aux;
    }
    
    // find the array and elements type
    n.getDataType();
    DataType edt = n.getElementDataType();
    
    // visit elements to sext or zext their values
    for(ArrayElement *ae : n.getElements()) {
        ae->value = coerceTo(ae->value, edt);
    }

    return NULL;
}

Node* PropagateTypes::visit(UpdateArray& n) {
    propagateChildren(n);
    // find the array type, based on elements
    DataType edt = n.getElementDataType();

    // visit expr to sext or zext their values
    n.setExpr(coerceTo(n.getExpr(), edt));

    return NULL;
}

Node* PropagateTypes::visit(UserType& n) {
    n.dt = n.getDataType();
    propagateChildren(n);
    return NULL;
}

Node* PropagateTypes::visit(Enum& n) {
    n.getDataType();
    //propagateChildren(n);
    return NULL;
}

Node* PropagateTypes::visit(Variable& n) {
    
    propagateChildren(n);
    
    Node *firstDecl = n.getScope()->findSymbol(n.getName());
    DataType sameNameDt = buildTypes->getType(n.getName());
    if (sameNameDt != BuildTypes::undefinedType) {
        yyerrorcpp(string_format("The name %s is already used to define a type.", n.getName().c_str()), &n);
        if (firstDecl)
            yywarncpp(string_format("The type %s was defined here.", n.getName().c_str()), firstDecl);

    } else if (firstDecl && firstDecl != &n) {
        DataType ndt = n.getDataType();
        DataType fdt = firstDecl->getDataType();
        if (ndt != BuildTypes::undefinedType &&
            fdt != BuildTypes::undefinedType &&
            ndt != fdt) {
            // the var was first defined as fdt.
            // we coherce the right hand side to match it
            Node *result = NULL;
            if (Scalar *sc = dynamic_cast<Scalar*>(&n)) {
                result = coerceTo(sc->expr(), fdt);
                sc->setExpr(result);
            }
            if (!result)
                yywarncpp(string_format("The symbol %s was first defined here.", n.getName().c_str()), firstDecl);
        }
    }
    return NULL;
}

Node* PropagateTypes::visit(Scalar& n) {
    
    Node *result = visit((Variable&)n);
    
    // although this should be done on SymbolizeTree,
    // some type propagarion in the tree change symbols
    // for scalars (e.g. FunctionCall -> ConstructorCall)
    auto& exprSymbols = n.expr()->getSymbols();
    if (exprSymbols.size() > 0)
        n.symbols = exprSymbols;
    return NULL;
}

Node* PropagateTypes::visit(Load& n) {
    // although this should be done on SymbolizeTree,
    // some type propagarion in the tree change symbols
    // for scalars (e.g. FunctionCall -> ConstructorCall)
    visit((Node&)n);
    Node *identSymbol = n.getIdentSymbol(false);
    if (identSymbol)
        n.symbols = identSymbol->getSymbols();
    return NULL;
}

Node* PropagateTypes::visit(MemCopy& n) {
    // although this should be done on SymbolizeTree,
    // some type propagarion in the tree change symbols
    // for scalars (e.g. FunctionCall -> ConstructorCall)
    visit((Node&)n);
    if (n.children().size() > 0)
        n.symbols = n.children()[0]->getSymbols();
    return NULL;
}
