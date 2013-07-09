#include "AssignOperationNode.hpp"
#include "VariableNode.hpp"
#include "indent.hpp"
#include "llvm/Type.h"
#include "llvm/Instructions.h"
#include "llvm/LLVMContext.h"
#include <string>
#include <iostream>
#include <map>

using std::cout;
using std::string;
using std::map;
using llvm::AllocaInst;
using llvm::Type;

template <> const char * const BinaryOperationTraits <AssignOp>::sign = "=";
template <> BinaryOperationGenerator BinaryOperationTraits <AssignOp>::generator (0);

AssignOperationNode::AssignOperationNode (const string & name, IASTNode * expression)
	: BinaryOperationNode <BinaryOperationTraits <AssignOp> > (new VariableNode (name), expression) { }

void AssignOperationNode::Print (size_t indent) const {
	print_indent (indent);

	this->left->Print ();
	cout << " = ";
	this->right->Print ();
}

Value * AssignOperationNode::GenerateCode (CodeGeneratorState & state) const {
	Value * assign_value = this->right->GenerateCode (state);
	const string & name = ((VariableNode *) this->left.get ())->GetName ();
	map <string, AllocaInst *>::const_iterator it = state.function->local_vars.find (name);

	if (it != state.function->local_vars.end ())
		return state.builder->CreateStore (assign_value, it->second);
	else {
		AllocaInst * var = state.builder->CreateAlloca (Type::getDoubleTy (llvm::getGlobalContext ()), 0, name.c_str ());
		state.function->local_vars [name] = var;
		return state.builder->CreateStore (assign_value, var);
	}
}

