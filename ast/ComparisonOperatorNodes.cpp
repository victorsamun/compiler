#include "ComparisonOperatorNodes.hpp"
#include "new_functional.hpp"
#include <memory>

using std::auto_ptr;

template <> const char * const BinaryOperationTraits <EqOp>::sign = "==";
template <> const char * const BinaryOperationTraits <NotEqOp>::sign = "!=";
template <> const char * const BinaryOperationTraits <GreaterOp>::sign = ">";
template <> const char * const BinaryOperationTraits <GreaterEqOp>::sign = ">=";
template <> const char * const BinaryOperationTraits <LessOp>::sign = "<";
template <> const char * const BinaryOperationTraits <LessEqOp>::sign = "<=";

template <> BinaryOperationGenerator BinaryOperationTraits <EqOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFCmpOEQ));
template <> BinaryOperationGenerator BinaryOperationTraits <NotEqOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFCmpONE));
template <> BinaryOperationGenerator BinaryOperationTraits <GreaterOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFCmpOGT));
template <> BinaryOperationGenerator BinaryOperationTraits <GreaterEqOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFCmpOGE));
template <> BinaryOperationGenerator BinaryOperationTraits <LessOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFCmpOLT));
template <> BinaryOperationGenerator BinaryOperationTraits <LessEqOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFCmpOLE));

