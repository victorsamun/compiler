#include "IfThenElseNode.hpp"
#include "indent.hpp"
#include <iostream>
#include "llvm/LLVMContext.h"
#include "llvm/BasicBlock.h"

using std::cout;
using std::endl;
using llvm::BasicBlock;

IfThenElseNode::IfThenElseNode (IASTNode * cond, IASTNode * then_branch, IASTNode * else_branch)
	: cond (cond), then_branch (then_branch), else_branch (else_branch) { }

void IfThenElseNode::Print (size_t indent) const {
	print_indent (indent);
	cout << "if ";
	this->cond->Print ();

	cout << " ->" << endl;
	this->then_branch->Print (indent);

	if (this->else_branch.get ()) {
		cout << endl;
		print_indent (indent);
		cout << "| ";
		this->else_branch->Print (indent);
	}
}

Value * IfThenElseNode::GenerateCode (CodeGeneratorState & state) const {
	BasicBlock * cond_true;
	BasicBlock * cond_false;
	BasicBlock * cond_end;
	Value * result;

	cond_end = BasicBlock::Create (llvm::getGlobalContext (), "label", state.function->function);

	cond_true = BasicBlock::Create (llvm::getGlobalContext (), "label", state.function->function);
	state.builder->SetInsertPoint (cond_true);
	CodeGeneratorState cond_true_state = state.ChangeBlock (cond_true);
	this->then_branch->GenerateCode (cond_true_state);
	state.builder->CreateBr (cond_end);

	if (this->else_branch.get ()) {
		cond_false = BasicBlock::Create (llvm::getGlobalContext (), "label", state.function->function);
		state.builder->SetInsertPoint (cond_false);
		CodeGeneratorState cond_false_state = state.ChangeBlock (cond_false);
		this->else_branch->GenerateCode (cond_false_state);
		state.builder->CreateBr (cond_end);
	}

	state.builder->SetInsertPoint (state.block);
	result = state.builder->CreateCondBr (this->cond->GenerateCode (state), cond_true, this->else_branch.get () ? cond_false : cond_end);

	state.block = cond_end;
	state.builder->SetInsertPoint (state.block);

	return result;
}

