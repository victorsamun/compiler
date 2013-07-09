#ifndef _NUMBER_NODE_HPP_
#define _NUMBER_NODE_HPP_

#include "IASTNode.hpp"

class NumberNode : public IASTNode {
	double val;

public:
	NumberNode (double val);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

