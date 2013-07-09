#include "TrueNode.hpp"
#include "indent.hpp"
#include <iostream>
#include "llvm/Type.h"
#include "llvm/LLVMContext.h"
#include "llvm/Constants.h"

using std::cout;
using llvm::ConstantInt;
using llvm::Type;

void TrueNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "true";
}

Value * TrueNode::GenerateCode (CodeGeneratorState & state) const {
	return ConstantInt::getTrue (Type::getInt1Ty (llvm::getGlobalContext ()));
}

