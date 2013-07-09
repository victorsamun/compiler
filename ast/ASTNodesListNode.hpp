#ifndef _AST_NODES_LIST_NODE_HPP_
#define _AST_NODES_LIST_NODE_HPP_

#include <list>
#include "IASTNode.hpp"
#include "shared_ptr.hpp"

using std::list;

class ASTNodesListNode : public IASTNode {
	list <shared_ptr <IASTNode> > exprs;

public:
	void Add (IASTNode * expr);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

