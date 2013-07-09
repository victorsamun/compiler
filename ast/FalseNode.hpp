#ifndef _FALSE_NODE_HPP_
#define _FALSE_NODE_HPP_

#include "IASTNode.hpp"

struct FalseNode : public IASTNode {
	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

