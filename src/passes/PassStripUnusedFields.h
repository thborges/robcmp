#pragma once

#include "llvm/IR/PassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Type.h"

#include "BackLLVM.h"

using namespace llvm;
using namespace std;


struct StripUnusedParentFieldsPass : PassInfoMixin<StripUnusedParentFieldsPass> {
    
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
        map<Type*, Type*> modifiedTypes;

        for(auto& structName : unusedParents) {           
            StructType *oldTy = StructType::getTypeByName(M.getContext(), structName);
            
            if (!oldTy || oldTy->isOpaque() || oldTy->getNumElements() == 0)
                continue;

            oldTy->setName(oldTy->getName().str() + ".discard");

            // Prepare new element list without parent (last field)
            ArrayRef<Type*> elements = oldTy->elements();
            std::vector<Type*> newElements(elements.begin(), elements.end() - 1);

            // Create the new StructType
            StructType *newTy = StructType::create(oldTy->getContext(), newElements,
                structName, oldTy->isPacked());

            modifiedTypes[oldTy] = newTy;
        }

        // identify structs that depends on the old type
        for (StructType *S : M.getIdentifiedStructTypes()) {
            if (S->isOpaque())
                continue;

            bool changed = false;
            vector<Type*> newElements;
            for(int i = 0; i < S->getNumElements(); i++) {
                auto element = modifiedTypes.find(S->getElementType(i));
                if (element != modifiedTypes.end()) {
                    newElements.push_back(element->second);
                    changed = true;
                } else {
                    newElements.push_back(S->getElementType(i));
                }
            }

            // change old structure name and create a new one
            if (changed) {
                string name = S->getName().str();
                S->setName(S->getName().str() + ".discard");
                StructType *newTy = StructType::create(S->getContext(), newElements,    
                    name, S->isPacked());
                modifiedTypes[S] = newTy;
            }
        }

        for(auto& [oldty, newty] : modifiedTypes) {
            replaceGlobals(M, oldty, newty);
            replaceGEP(M, oldty, newty);
        }

        return PreservedAnalyses::all();
    }

    void replaceGlobals(Module &M, Type *oldty, Type *newty) {
        
        // Find globals of the old type
        std::vector<GlobalVariable*> toReplace;
        for (GlobalVariable &GV : M.globals()) {
            if (GV.getValueType() == oldty) {
                toReplace.push_back(&GV);
            }
        }

        for (GlobalVariable *GV : toReplace) {
            auto *newGV = new GlobalVariable(M, newty, GV->isConstant(), GV->getLinkage(),
                GV->getInitializer(), GV->getName(), nullptr, GV->getThreadLocalMode(), GV->getAddressSpace()
            );
            GV->replaceAllUsesWith(newGV);
            GV->eraseFromParent();
        }
    }

    void replaceGEP(Module &M, Type *oldty, Type *newty) {
        std::vector<GetElementPtrInst*> toReplace;
        //std::vector<StoreInst*> toReplaceStore;
        std::vector<ReturnInst*> toReplaceReturn;

        // Collect all GEPs using oldty
        for (Function &F : M) {
            for (BasicBlock &BB : F) {
                for (Instruction &I : BB) {
                    if (auto *GEP = dyn_cast<GetElementPtrInst>(&I)) {
                        if (GEP->getSourceElementType() == oldty) {
                            toReplace.push_back(GEP);
                        }
                    } /*else if (auto *Store = dyn_cast<StoreInst>(&I)) {
                        auto *val = Store->getPointerOperand();
                        if (isa<GetElementPtrInst>(val)) {
                            auto *GEP = cast<GetElementPtrInst>(val);
                            if (GEP->getSourceElementType() == oldty) {
                                GEP->print(errs()); 
                                errs() << "\n";
                                Store->print(errs());
                                errs() << "\n";
                                //toReplaceStore.push_back(Store);
                            }
                        }
                    }*/
                    else if (auto *Return = dyn_cast<ReturnInst>(&I)) {
                        auto *val = Return->getReturnValue();
                        if (!val) continue;                    
                        if (auto *CE = dyn_cast<ConstantExpr>(val)) {
                            if (CE->getOpcode() == Instruction::GetElementPtr) {
                                const auto *GO = cast<GEPOperator>(CE);
                                if (GO->getSourceElementType() == oldty) {
                                    toReplaceReturn.push_back(Return);
                                }
                            }
                        }
                    }
                }
            }
        }

        auto createNewGEP = [](IRBuilder<> &B, Type *newty, GetElementPtrInst *GEP) {
            Value *ptr = GEP->getPointerOperand();
            SmallVector<Value*, 4> indices(GEP->idx_begin(), GEP->idx_end());
            Value *newGEP = B.CreateGEP(newty, ptr, indices);
            newGEP->setName(GEP->getName());
            return newGEP;
        };

        for (GetElementPtrInst *GEP : toReplace) {
            IRBuilder<> B(GEP);
            if (GEP->getSourceElementType() == nullptr)
                continue;
            auto *newGEP = createNewGEP(B, newty, GEP);
            GEP->replaceAllUsesWith(newGEP);
            GEP->eraseFromParent();
        }

        /*for (StoreInst *Store : toReplaceStore) {
            IRBuilder<> B(Store);
            auto *val = Store->getPointerOperand();
            auto *GEP = cast<GetElementPtrInst>(val);
            auto *newGEP = createNewGEP(B, newty, GEP);

            auto *newStore = B.CreateStore(Store->getValueOperand(), newGEP, Store->isVolatile());
            Store->replaceAllUsesWith(newStore);
            Store->eraseFromParent();
        }*/

        for (ReturnInst *Return : toReplaceReturn) {
            IRBuilder<> B(Return);
            
            auto *val = Return->getReturnValue();
            auto *CE = dyn_cast<ConstantExpr>(val);
            const auto *GO = cast<GEPOperator>(CE);        

            Value *ptr = CE->getOperand(0);
            SmallVector<Value*, 4> indices(GO->idx_begin(), GO->idx_end());
            Value *newGEP = B.CreateGEP(newty, ptr, indices);
            newGEP->setName(GO->getName());

            auto *newReturn = B.CreateRet(newGEP);
            Return->replaceAllUsesWith(newReturn);
            Return->eraseFromParent();
        }
    }
};
