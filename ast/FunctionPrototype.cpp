#include "FunctionPrototype.hpp"
#include <string>

using std::string;

FunctionPrototype::FunctionPrototype (const string & name, ParametersList * params)
	: name (name), params (params->params) { }

