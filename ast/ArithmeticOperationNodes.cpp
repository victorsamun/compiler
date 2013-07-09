#include "ArithmeticOperationNodes.hpp"

template <> const char * const BinaryOperationTraits <PlusOp>::sign = "+";
template <> const char * const BinaryOperationTraits <MinusOp>::sign = "-";
template <> const char * const BinaryOperationTraits <MultOp>::sign = "*";
template <> const char * const BinaryOperationTraits <DivOp>::sign = "/";

template <> BinaryOperationGenerator BinaryOperationTraits <PlusOp>::generator (& IRBuilder <>::CreateFAdd);
template <> BinaryOperationGenerator BinaryOperationTraits <MinusOp>::generator (& IRBuilder <>::CreateFSub);
template <> BinaryOperationGenerator BinaryOperationTraits <MultOp>::generator (& IRBuilder <>::CreateFMul);
template <> BinaryOperationGenerator BinaryOperationTraits <DivOp>::generator (& IRBuilder <>::CreateFDiv);

