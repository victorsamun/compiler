#include "ProgramNode.hpp"
#include <vector>
#include "llvm/Type.h"
#include "llvm/LLVMContext.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/DerivedTypes.h"
#include "llvm/BasicBlock.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include <map>
#include <string>

using llvm::IRBuilder;
using llvm::Type;
using llvm::PointerType;
using llvm::IntegerType;
using llvm::FunctionType;
using llvm::BasicBlock;
using std::vector;
using std::map;
using std::string;

Value * printf_fmt;
Value * scanf_fmt;

ProgramNode::ProgramNode (IASTNode * main)
	: main (main) { }

void ProgramNode::Print (size_t indent) const {
	this->main->Print (indent);
}

Value * ProgramNode::GenerateCode (CodeGeneratorState & state) const {
	state.builder = new IRBuilder <> (llvm::getGlobalContext ());
	state.module = new Module ("module.1", llvm::getGlobalContext ());

	Function * mainFunction = Function::Create (FunctionType::get (Type::getInt32Ty (llvm::getGlobalContext ()), vector <const Type *> (0), false), Function::ExternalLinkage, "main", state.module);
	BasicBlock * mainFunctionBlock = BasicBlock::Create (llvm::getGlobalContext (), "block", mainFunction);
	state.builder->SetInsertPoint (mainFunctionBlock);
	scanf_fmt = state.builder->CreateGlobalStringPtr ("%lg", ".scanf_fmt");
	printf_fmt = state.builder->CreateGlobalStringPtr ("%lg\n", ".printf_fmt");

	state.function = NULL;
	state.block = NULL;

	Function * printfFunction = Function::Create (FunctionType::get (Type::getVoidTy (llvm::getGlobalContext ()), vector <const Type *> (1, PointerType::get (IntegerType::get (llvm::getGlobalContext (), 8), 0)), true), Function::ExternalLinkage, "printf", state.module);

	Function * scanfFunction = Function::Create (FunctionType::get (Type::getVoidTy (llvm::getGlobalContext ()), vector <const Type *> (1, PointerType::get (IntegerType::get (llvm::getGlobalContext (), 8), 0)), true), Function::ExternalLinkage, "scanf", state.module);

	Value * result = this->main->GenerateCode (state);

	state.builder->SetInsertPoint (mainFunctionBlock);

	Function * MainFunction = state.module->getFunction ("Main");
	if (NULL == MainFunction)
		throw "No `Main' function";

	if (MainFunction->arg_size () != 0)
		throw "Prototype mismatch";

	state.builder->CreateRet (state.builder->CreateFPToSI (state.builder->CreateCall (MainFunction, "tmp"), Type::getInt32Ty (llvm::getGlobalContext ()), "tmp"));

	llvm::verifyFunction (* mainFunction);

	state.module->dump ();

	string error_string;
	llvm::raw_fd_ostream bitcode ("a.bc", error_string, 0);
	llvm::WriteBitcodeToFile (state.module, bitcode);
	bitcode.close ();

	return result;
}

