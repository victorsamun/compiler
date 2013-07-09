#ifndef _COMPARISON_OPERATION_NODES_HPP_
#define _COMPARISON_OPERATION_NODES_HPP_

#include "BinaryOperationNode.hpp"

struct EqOp { };
struct NotEqOp { };
struct GreaterOp { };
struct GreaterEqOp { };
struct LessOp { };
struct LessEqOp { };

typedef BinaryOperationNode <BinaryOperationTraits <EqOp> > EqualsOperatorNode;
typedef BinaryOperationNode <BinaryOperationTraits <NotEqOp> > NotEqualsOperatorNode;
typedef BinaryOperationNode <BinaryOperationTraits <GreaterOp> > GreaterOperatorNode;
typedef BinaryOperationNode <BinaryOperationTraits <GreaterEqOp> > GreaterEqualsOperatorNode;
typedef BinaryOperationNode <BinaryOperationTraits <LessOp> > LessOperatorNode;
typedef BinaryOperationNode <BinaryOperationTraits <LessEqOp> > LessEqualsOperatorNode;

#endif

