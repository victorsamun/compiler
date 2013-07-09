#ifndef _TRUE_NODE_HPP_
#define _TRUE_NODE_HPP_

#include "llvm/Value.h"
#include "IASTNode.hpp"
#include "CodeGeneratorState.hpp"

using llvm::Value;

struct TrueNode : public IASTNode {
	virtual void Print (size_t indent) const;
	virtual Value * GenerateCode (CodeGeneratorState & state) const;
};

#endif

