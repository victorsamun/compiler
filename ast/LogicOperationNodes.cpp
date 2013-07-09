#include "LogicOperationNodes.hpp"
#include "new_functional.hpp"
#include "indent.hpp"
#include <memory>
#include <iostream>

using std::auto_ptr;
using std::cout;

template <> const char * const BinaryOperationTraits <AndOp>::sign = "&&";
template <> const char * const BinaryOperationTraits <OrOp>::sign = "||";
template <> const char * const BinaryOperationTraits <XorOp>::sign = "^";

template <> BinaryOperationGenerator BinaryOperationTraits <AndOp>::generator
	(ptr_mem_fun3 <IRBuilder <>, Value *, Value *, const Twine &, Value *> (& IRBuilder <>::CreateAnd));
template <> BinaryOperationGenerator BinaryOperationTraits <OrOp>::generator
	(ptr_mem_fun3 <IRBuilder <>, Value *, Value *, const Twine &, Value *> (& IRBuilder <>::CreateOr));
template <> BinaryOperationGenerator BinaryOperationTraits <XorOp>::generator
	(ptr_mem_fun3 <IRBuilder <>, Value *, Value *, const Twine &, Value *> (& IRBuilder <>::CreateXor));

NotOperationNode::NotOperationNode (IASTNode * left)
	: left (left) { }

void NotOperationNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "!(";

	this->left->Print ();
	cout << ")";
}

Value * NotOperationNode::GenerateCode (CodeGeneratorState & state) const {
	return state.builder->CreateNot (this->left->GenerateCode (state), "tmp");
}

