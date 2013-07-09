#include "CodeGeneratorState.hpp"

CodeGeneratorState CodeGeneratorState::ChangeBlock (BasicBlock * block) const {
	CodeGeneratorState result;

	result.builder = this->builder;
	result.module = this->module;
	result.function = this->function;
	result.block = block;

	return result;
}

CodeGeneratorState CodeGeneratorState::BeginFunction (Function * function) const {
	CodeGeneratorState result;

	result.builder = this->builder;
	result.module = this->module;
	result.function = new FunctionStruct ();
	result.function->function = function;
	result.block = NULL;

	return result;
}
