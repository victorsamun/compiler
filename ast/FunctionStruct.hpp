#ifndef _FUNCTION_STRUCT_HPP_
#define _FUNCTION_STRUCT_HPP_

#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/Value.h"
#include <map>
#include <string>

using std::map;
using std::string;
using llvm::Function;
using llvm::AllocaInst;
using llvm::Value;

struct FunctionStruct {
	Function * function;
	map <string, AllocaInst *> local_vars;
	map <string, Value *> params;
};

#endif

