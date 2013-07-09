#ifndef _IF_THEN_ELSE_NODE_HPP_
#define _IF_THEN_ELSE_NODE_HPP_

#include "IASTNode.hpp"
#include <memory>

using std::auto_ptr;

class IfThenElseNode : public IASTNode {
	auto_ptr <IASTNode> cond;
	auto_ptr <IASTNode> then_branch;
	auto_ptr <IASTNode> else_branch;

public:
	IfThenElseNode (IASTNode * cond, IASTNode * then_branch, IASTNode * else_branch);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

