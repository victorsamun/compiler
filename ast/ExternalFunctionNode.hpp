#ifndef _EXTERNAL_FUNCTION_NODE_HPP_
#define _EXTERNAL_FUNCTION_NODE_HPP_

#include <string>
#include <list>
#include "IASTNode.hpp"
#include "FunctionPrototype.hpp"

using std::string;
using std::list;

class ExternalFunctionNode : public IASTNode {
	string name;
	list <string> params;

public:
	ExternalFunctionNode (FunctionPrototype * proto);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

