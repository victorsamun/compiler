#include "ReadNode.hpp"
#include "indent.hpp"
#include <iostream>
#include <string>
#include "ProgramNode.hpp"

using std::cout;
using std::string;

ReadNode::ReadNode (const string & name)
	: name (name) { }

void ReadNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "=>> " << this->name;
}

Value * ReadNode::GenerateCode (CodeGeneratorState & state) const {
	Value * result;
	state.builder->CreateCall2 (state.module->getFunction ("scanf"), scanf_fmt, result, "");

	return state.builder->CreateStore (state.builder->CreateLoad (result), state.function->local_vars [this->name]);
}

