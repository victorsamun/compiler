#ifndef _BINARY_OPERATION_TRAITS_HPP_
#define _BINARY_OPERATION_TRAITS_HPP_

#include <memory>
#include "llvm/Support/IRBuilder.h"
#include "llvm/Value.h"
#include "new_functional.hpp"

using llvm::IRBuilder;
using llvm::Value;
using llvm::Twine;
using std::auto_ptr;

typedef auto_ptr <fun_4arg <IRBuilder <> *, Value *, Value *, const Twine &, Value *> > BinaryOperationGenerator;
 
template <typename Operation>
struct BinaryOperationTraits {
	typedef Operation OperationType;

	static const char * const sign;
	static BinaryOperationGenerator generator;
};

#endif

