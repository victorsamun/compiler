#include "FunctionCallNode.hpp"
#include "indent.hpp"
#include "shared_ptr.hpp"
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include "llvm/Function.h"

using std::cout;
using std::list;
using std::string;
using std::vector;
using std::transform;
using std::back_inserter;
using std::bind2nd;
using std::mem_fun;
using llvm::Function;

FunctionCallNode::FunctionCallNode (const string & name, CallParametersList * params)
	: name (name), params (params) { }

void FunctionCallNode::Print (size_t indent) const {
	print_indent (indent);
	cout << this->name << " (";
	for (list <shared_ptr <IASTNode> >::const_iterator it = this->params->begin (); it != this->params->end (); ++ it) {
		if (it != this->params->begin ())
			cout << ", ";
		(* it)->Print ();
	}
	cout << ')';
}

Value * FunctionCallNode::GenerateCode (CodeGeneratorState & state) const {
	Function * callee = state.module->getFunction (this->name.c_str ());
	if (NULL == callee)
		throw "Unknown function called";

	if (callee->arg_size () != this->params->size ())
		throw "Prototype mismatch";

	vector <Value *> arguments;
	arguments.reserve (this->params->size ());
	transform (this->params->begin (), this->params->end (), back_inserter (arguments), bind2nd (mem_fun (& IASTNode::GenerateCode), state));

	return state.builder->CreateCall (callee, arguments.begin (), arguments.end (), "tmp");
}

