#ifndef _BINARY_OPERATION_TRAITS_HPP_
#define _BINARY_OPERATION_TRAITS_HPP_

#include "llvm/Support/IRBuilder.h"
#include "llvm/Value.h"

using llvm::IRBuilder;
using llvm::Value;
using llvm::Twine;

typedef Value * (IRBuilder <>::* BinaryOperationGenerator) (Value *, Value *, const Twine &);
 
template <typename Operation>
struct BinaryOperationTraits {
	typedef Operation OperationType;

	static const char * const sign;
	static BinaryOperationGenerator generator;
};

#endif

