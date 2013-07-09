#ifndef _ARITHMETIC_OPERATION_NODES_HPP_
#define _ARITHMETIC_OPERATION_NODES_HPP_

#include "BinaryOperationNode.hpp"

struct PlusOp { };
struct MinusOp { };
struct MultOp { };
struct DivOp { };

typedef BinaryOperationNode <BinaryOperationTraits <PlusOp> > PlusOperationNode;
typedef BinaryOperationNode <BinaryOperationTraits <MinusOp> > MinusOperationNode;
typedef BinaryOperationNode <BinaryOperationTraits <MultOp> > MultiplicationOperationNode;
typedef BinaryOperationNode <BinaryOperationTraits <DivOp> > DivisionOperationNode;

#endif

