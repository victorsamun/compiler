#include "FunctionDefinitionNode.hpp"
#include "indent.hpp"
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include "llvm/Function.h"
#include "llvm/Type.h"
#include "llvm/LLVMContext.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Analysis/Verifier.h"

using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::string;
using llvm::Function;
using llvm::FunctionType;
using llvm::Type;

FunctionDefinitionNode::FunctionDefinitionNode (FunctionPrototype * proto, ASTNodesListNode * exprs)
	: name (proto->name), params (proto->params), exprs (exprs) { }

void FunctionDefinitionNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "sub " << this->name << " [";
	for (list <string>::const_iterator it = this->params.begin (); it != this->params.end (); ++ it) {
		if (it != this->params.begin ())
			cout << ", ";
		cout << * it;
	}
	cout << "]" << endl;

	this->exprs->Print (indent);
}

Value * FunctionDefinitionNode::GenerateCode (CodeGeneratorState & state) const {
	if (state.module->getFunction (this->name.c_str ()) != NULL)
		throw "Redefinition of function";

	vector <const Type *> arguments (this->params.size (), Type::getDoubleTy (llvm::getGlobalContext ()));
	FunctionType * functionType = FunctionType::get (Type::getDoubleTy (llvm::getGlobalContext ()), arguments, false);
	Function * function = Function::Create (functionType, Function::ExternalLinkage, this->name.c_str (), state.module);

	CodeGeneratorState new_state = state.BeginFunction (function);

	Function::arg_iterator arg_it = function->arg_begin ();
	list <string>::const_iterator param_it = this->params.begin ();
	for (; param_it != this->params.end (); ++ arg_it, ++ param_it) {
		arg_it->setName (* param_it);
		new_state.function->params [* param_it] = arg_it;
	}

	new_state.block = BasicBlock::Create (llvm::getGlobalContext (), "block", function);
	state.builder->SetInsertPoint (new_state.block);

	this->exprs->GenerateCode (new_state);

	verifyFunction (* function);
	return function;
}

