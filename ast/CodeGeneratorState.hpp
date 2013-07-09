#ifndef _CODE_GENERATOR_STATE_HPP_
#define _CODE_GENERATOR_STATE_HPP_

#include "llvm/Support/IRBuilder.h"
#include "llvm/Value.h"
#include "llvm/Module.h"
#include "llvm/BasicBlock.h"
#include "FunctionStruct.hpp"

using llvm::IRBuilder;
using llvm::Module;
using llvm::BasicBlock;
using llvm::Value;

struct CodeGeneratorState {
	IRBuilder <> * builder;
	Module * module;
	FunctionStruct * function;
	BasicBlock * block;

	CodeGeneratorState ChangeBlock (BasicBlock *) const;
	CodeGeneratorState BeginFunction (Function *) const;
};

#endif

