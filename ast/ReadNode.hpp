#ifndef _READ_NODE_HPP_
#define _READ_NODE_HPP_

#include <string>
#include "IASTNode.hpp"

using std::string;

class ReadNode : public IASTNode {
	string name;

public:
	ReadNode (const string & name);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

