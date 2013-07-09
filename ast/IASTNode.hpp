#ifndef _IASTNODE_HPP_
#define _IASTNODE_HPP_

#include "llvm/Value.h"
#include <cstdlib>
#include "CodeGeneratorState.hpp"

using llvm::Value;

class IASTNode {
	IASTNode (const IASTNode &);
	IASTNode & operator = (const IASTNode &);
public:
	IASTNode (void);
	virtual void Print (size_t indent = 0) const = 0;
	virtual Value * GenerateCode (CodeGeneratorState & state) const = 0;
	virtual ~IASTNode (void);
};

#endif

