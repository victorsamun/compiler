#include "ReturnNode.hpp"
#include "indent.hpp"
#include <iostream>

using std::cout;

ReturnNode::ReturnNode (IASTNode * expr)
	: expr (expr) { }

void ReturnNode::Print (size_t indent) const {
	print_indent (indent);

	cout << "ret ";
	this->expr->Print ();
}

Value * ReturnNode::GenerateCode (CodeGeneratorState & state) const {
	return state.builder->CreateRet (this->expr->GenerateCode (state));
}

