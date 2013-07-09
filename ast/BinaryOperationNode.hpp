#ifndef _BINARY_OPERATION_NODE_HPP_
#define _BINARY_OPERATION_NODE_HPP_

#include <string>
#include <iostream>
#include <memory>
#include "llvm/Value.h"
#include "IASTNode.hpp"
#include "BinaryOperationTraits.hpp"
#include "indent.hpp"

using std::string;
using std::cout;
using std::auto_ptr;
using llvm::Value;

template <typename OperationTraits>
class BinaryOperationNode : public IASTNode {
protected:
	auto_ptr <IASTNode> left;
	auto_ptr <IASTNode> right;

public:
	typedef typename OperationTraits::OperationType OperationType;

	BinaryOperationNode (IASTNode * left, IASTNode * right)
		: left (left), right (right) { }

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
	virtual ~BinaryOperationNode (void) { }
};

template <typename OperationTraits>
void BinaryOperationNode <OperationTraits>::Print (size_t indent) const {
	print_indent (indent);
	cout << '(';

	if (this->left.get ()) {
		if (! this->right.get ())
			cout << OperationTraits::sign << ' ';

		this->left->Print ();

		if (this->right.get ())
			cout << ' ' << OperationTraits::sign << ' ';
	}

	if (this->right.get ())
		this->right->Print ();

	cout << ')';
}

template <typename OperationTraits>
Value * BinaryOperationNode <OperationTraits>::GenerateCode (CodeGeneratorState & state) const {
	return (state.builder->*(OperationTraits::generator)) (this->left->GenerateCode (state), this->right->GenerateCode (state), "tmp");
}

#endif

