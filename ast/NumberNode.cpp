#include "NumberNode.hpp"
#include "indent.hpp"
#include "llvm/Constants.h"
#include "llvm/LLVMContext.h"
#include "llvm/DerivedTypes.h"
#include <iostream>

using std::cout;
using llvm::ConstantFP;
using llvm::APFloat;

NumberNode::NumberNode (double val)
	: val (val) { }

void NumberNode::Print (size_t indent) const {
	print_indent (indent);
	cout << this->val;
}

Value * NumberNode::GenerateCode (CodeGeneratorState & state) const {
	return ConstantFP::get (llvm::getGlobalContext (), APFloat (this->val));
}

