#ifndef _FUNCTION_CALL_NODE_HPP_
#define _FUNCTION_CALL_NODE_HPP_

#include <string>
#include <list>
#include "IASTNode.hpp"
#include "CallParametersList.hpp"

using std::string;

class FunctionCallNode : public IASTNode {
	string name;
	CallParametersList * params;

public:
	FunctionCallNode (const string & name, CallParametersList * params);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

