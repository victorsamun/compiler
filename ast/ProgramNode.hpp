#ifndef _PROGRAM_NODE_HPP_
#define _PROGRAM_NODE_HPP_

#include "IASTNode.hpp"
#include <memory>

extern Value * printf_fmt;
extern Value * scanf_fmt;

using std::auto_ptr;

class ProgramNode : public IASTNode {
	auto_ptr <IASTNode> main;

public:
	ProgramNode (IASTNode * main);

	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

