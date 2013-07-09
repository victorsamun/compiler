#include "WriteNode.hpp"
#include "indent.hpp"
#include <iostream>
#include "ProgramNode.hpp"

using std::cout;

WriteNode::WriteNode (IASTNode * expr)
	: expr (expr) { }

void WriteNode::Print (size_t indent) const {
	print_indent (indent);

	cout << "<<= ";
	this->expr->Print ();
}

Value * WriteNode::GenerateCode (CodeGeneratorState & state) const {
	state.builder->CreateCall2 (state.module->getFunction ("printf"), printf_fmt, expr->GenerateCode (state));
}

