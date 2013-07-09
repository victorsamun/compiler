#include "LogicOperationNodes.hpp"
#include "indent.hpp"
#include <iostream>

using std::cout;

template <> const char * const BinaryOperationTraits <AndOp>::sign = "&&";
template <> const char * const BinaryOperationTraits <OrOp>::sign = "||";
template <> const char * const BinaryOperationTraits <XorOp>::sign = "^";

template <> BinaryOperationGenerator BinaryOperationTraits <AndOp>::generator (& IRBuilder <>::CreateAnd);
template <> BinaryOperationGenerator BinaryOperationTraits <OrOp>::generator (& IRBuilder <>::CreateOr);
template <> BinaryOperationGenerator BinaryOperationTraits <XorOp>::generator (& IRBuilder <>::CreateXor);

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

