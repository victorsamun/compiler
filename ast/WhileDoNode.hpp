#ifndef _WHILE_DO_NODE_HPP_
#define _WHILE_DO_NODE_HPP_

#include "IASTNode.hpp"
#include <memory>

using std::auto_ptr;

class WhileDoNode : public IASTNode {
	auto_ptr <IASTNode> cond;
	auto_ptr <IASTNode> block;

public:
	WhileDoNode (IASTNode * cond, IASTNode * block);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

