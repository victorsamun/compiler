#include "VariableNode.hpp"
#include "NumberNode.hpp"
#include "indent.hpp"
#include "llvm/Instructions.h"
#include <string>
#include <iostream>
#include <map>

using std::cout;
using std::string;
using std::map;
using llvm::AllocaInst;

VariableNode::VariableNode (const string & name)
	: name (name) { }

const string & VariableNode::GetName (void) const {
	return this->name;
}

void VariableNode::Print (size_t indent) const {
	print_indent (indent);
	cout << this->name;
}

Value * VariableNode::GenerateCode (CodeGeneratorState & state) const {
	map <string, AllocaInst *>::const_iterator it = state.function->local_vars.find (this->name);

	if (it != state.function->local_vars.end ())
		return state.builder->CreateLoad (it->second);
	else {
		map <string, Value *>::const_iterator param_it = state.function->params.find (this->name);
		if (param_it != state.function->params.end ())
			return param_it->second;
		else
			return (new NumberNode (0.0))->GenerateCode (state);
	}
}

