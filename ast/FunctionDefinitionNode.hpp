#ifndef _FUNCTION_DEFINITION_NODE_HPP_
#define _FUNCTION_DEFINITION_NODE_HPP_

#include <string>
#include <list>
#include <memory>
#include "IASTNode.hpp"
#include "ASTNodesListNode.hpp"
#include "FunctionPrototype.hpp"

using std::string;
using std::list;
using std::auto_ptr;

class FunctionDefinitionNode : public IASTNode
{
	string name;
	list <string> params;
	auto_ptr <ASTNodesListNode> exprs;

public:
	FunctionDefinitionNode (FunctionPrototype * proto, ASTNodesListNode * exprs);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

