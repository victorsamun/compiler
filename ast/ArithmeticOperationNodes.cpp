#include "ArithmeticOperationNodes.hpp"
#include "new_functional.hpp"
#include <memory>

using std::auto_ptr;

template <> const char * const BinaryOperationTraits <PlusOp>::sign = "+";
template <> const char * const BinaryOperationTraits <MinusOp>::sign = "-";
template <> const char * const BinaryOperationTraits <MultOp>::sign = "*";
template <> const char * const BinaryOperationTraits <DivOp>::sign = "/";

template <> BinaryOperationGenerator BinaryOperationTraits <PlusOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFAdd));
template <> BinaryOperationGenerator BinaryOperationTraits <MinusOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFSub));
template <> BinaryOperationGenerator BinaryOperationTraits <MultOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFMul));
template <> BinaryOperationGenerator BinaryOperationTraits <DivOp>::generator (ptr_mem_fun3 (& IRBuilder <>::CreateFDiv));

