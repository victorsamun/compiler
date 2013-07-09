#ifndef _ASSIGN_OPERATION_NODE_HPP_
#define _ASSIGN_OPERATION_NODE_HPP_

#include <string>
#include "IASTNode.hpp"
#include "BinaryOperationNode.hpp"

class AssignOp { };

using std::string;

class AssignOperationNode : public BinaryOperationNode <BinaryOperationTraits <AssignOp> > {
public:
	AssignOperationNode (const string & name, IASTNode * expression);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

