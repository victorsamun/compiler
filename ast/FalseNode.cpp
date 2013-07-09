#include "FalseNode.hpp"
#include "indent.hpp"
#include <iostream>
#include "llvm/Type.h"
#include "llvm/LLVMContext.h"
#include "llvm/Constants.h"

using std::cout;
using llvm::ConstantInt;
using llvm::Type;

void FalseNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "false";
}

Value * FalseNode::GenerateCode (CodeGeneratorState & state) const {
	return ConstantInt::getFalse (Type::getInt1Ty (llvm::getGlobalContext ()));
}

