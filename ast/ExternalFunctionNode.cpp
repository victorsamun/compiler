#include "ExternalFunctionNode.hpp"
#include "indent.hpp"
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include "llvm/Function.h"
#include "llvm/Type.h"
#include "llvm/LLVMContext.h"

using std::cout;
using std::list;
using std::string;
using std::vector;
using llvm::Function;
using llvm::Type;
using llvm::FunctionType;

ExternalFunctionNode::ExternalFunctionNode (FunctionPrototype * proto)
	: name (proto->name), params (proto->params) { }

void ExternalFunctionNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "load " << this->name << " (";
	for (list <string>::const_iterator it = this->params.begin (); it != this->params.end (); ++ it) {
		if (it != this->params.begin ())
			cout << ", ";

		cout << * it;
	}
	cout << ')';
}

Value * ExternalFunctionNode::GenerateCode (CodeGeneratorState & state) const {
	if (state.module->getFunction (this->name.c_str ()) != NULL)
		throw "Redefinition of function";

	vector <const Type *> arguments (this->params.size (), Type::getDoubleTy (llvm::getGlobalContext ()));
	FunctionType * functionType = FunctionType::get (Type::getDoubleTy (llvm::getGlobalContext ()), arguments, false);
	Function * function = Function::Create (functionType, Function::ExternalLinkage, this->name.c_str (), state.module);

	return function;
}

