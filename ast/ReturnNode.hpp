#ifndef _RETURN_NODE_HPP_
#define _RETURN_NODE_HPP_

#include "IASTNode.hpp"
#include <memory>

using std::auto_ptr;

class ReturnNode : public IASTNode {
	auto_ptr <IASTNode> expr;

public:
	ReturnNode (IASTNode * expr);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

