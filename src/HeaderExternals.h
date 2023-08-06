
#pragma once

/* Add only std cpp library related includes */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <sstream>

using namespace std;

/* Add only llvm related includes */

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/ADT/StringExtras.h>

using namespace llvm;
