#include "WhileDoNode.hpp"
#include "indent.hpp"
#include <iostream>
#include "llvm/LLVMContext.h"
#include "llvm/BasicBlock.h"

using std::cout;
using std::endl;
using llvm::BasicBlock;

WhileDoNode::WhileDoNode (IASTNode * cond, IASTNode * block)
	: cond (cond), block (block) { }

void WhileDoNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "while ";
	this->cond->Print ();

	cout << " do" << endl;
	this->block->Print (indent);
}

Value * WhileDoNode::GenerateCode (CodeGeneratorState & state) const {
	BasicBlock * loop_cond;
	BasicBlock * loop_body;
	BasicBlock * loop_end;
	Value * result;

	loop_end = BasicBlock::Create (llvm::getGlobalContext (), "label", state.function->function);

	loop_cond = BasicBlock::Create (llvm::getGlobalContext (), "label", state.function->function);
	state.builder->CreateBr (loop_cond);

	loop_body = BasicBlock::Create (llvm::getGlobalContext (), "label", state.function->function);
	state.builder->SetInsertPoint (loop_body);
	CodeGeneratorState loop_body_state = state.ChangeBlock (loop_body);
	this->block->GenerateCode (loop_body_state);
	state.builder->CreateBr (loop_cond);

	state.builder->SetInsertPoint (loop_cond);
	CodeGeneratorState loop_cond_state = state.ChangeBlock (loop_cond);
	result = state.builder->CreateCondBr (this->cond->GenerateCode (loop_cond_state), loop_body, loop_end);
	state.block = loop_end;
	state.builder->SetInsertPoint (state.block);

	return result;	
}

