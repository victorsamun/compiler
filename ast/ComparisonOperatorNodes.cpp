#include "ComparisonOperatorNodes.hpp"

template <> const char * const BinaryOperationTraits <EqOp>::sign = "==";
template <> const char * const BinaryOperationTraits <NotEqOp>::sign = "!=";
template <> const char * const BinaryOperationTraits <GreaterOp>::sign = ">";
template <> const char * const BinaryOperationTraits <GreaterEqOp>::sign = ">=";
template <> const char * const BinaryOperationTraits <LessOp>::sign = "<";
template <> const char * const BinaryOperationTraits <LessEqOp>::sign = "<=";

template <> BinaryOperationGenerator BinaryOperationTraits <EqOp>::generator (& IRBuilder <>::CreateFCmpOEQ);
template <> BinaryOperationGenerator BinaryOperationTraits <NotEqOp>::generator (& IRBuilder <>::CreateFCmpONE);
template <> BinaryOperationGenerator BinaryOperationTraits <GreaterOp>::generator (& IRBuilder <>::CreateFCmpOGT);
template <> BinaryOperationGenerator BinaryOperationTraits <GreaterEqOp>::generator (& IRBuilder <>::CreateFCmpOGE);
template <> BinaryOperationGenerator BinaryOperationTraits <LessOp>::generator (& IRBuilder <>::CreateFCmpOLT);
template <> BinaryOperationGenerator BinaryOperationTraits <LessEqOp>::generator (& IRBuilder <>::CreateFCmpOLE);

