#ifndef _FUNCTION_PROTOTYPE_HPP_
#define _FUNCTION_PROTOTYPE_HPP_

#include <string>
#include <list>
#include "ParametersList.hpp"

using std::string;
using std::list;

struct FunctionPrototype {
	string name;
	list <string> params;

	FunctionPrototype (const string & name, ParametersList * params);
};

#endif

