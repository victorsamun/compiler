#ifndef _LOGIC_OPERATION_NODES_HPP_
#define _LOGIC_OPERATION_NODES_HPP_

#include "BinaryOperationNode.hpp"
#include "IASTNode.hpp"
#include <memory>

struct AndOp { };
struct OrOp { };
struct XorOp { };

typedef BinaryOperationNode <BinaryOperationTraits <AndOp> > AndOperationNode;
typedef BinaryOperationNode <BinaryOperationTraits <OrOp> > OrOperationNode;
typedef BinaryOperationNode <BinaryOperationTraits <XorOp> > XorOperationNode;

using std::auto_ptr;

class NotOperationNode : public IASTNode {
	auto_ptr <IASTNode> left;
public:
	NotOperationNode (IASTNode * left);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

