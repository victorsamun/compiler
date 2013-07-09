#ifndef _VARIABLE_NODE_HPP_
#define _VARIABLE_NODE_HPP_

#include <string>
#include "IASTNode.hpp"

using std::string;

class VariableNode : public IASTNode {
	string name;

public:
	VariableNode (const string & name);

	const string & GetName (void) const;
	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

