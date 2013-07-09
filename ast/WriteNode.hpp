#ifndef _WRITE_NODE_HPP_
#define _WRITE_NODE_HPP_

#include "IASTNode.hpp"
#include <memory>

using std::auto_ptr;

class WriteNode : public IASTNode {
	auto_ptr <IASTNode> expr;

public:
	WriteNode (IASTNode * expr);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

