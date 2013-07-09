#ifndef _PARAMETERS_LIST_HPP_
#define _PARAMETERS_LIST_HPP_

#include <string>
#include <list>

using std::string;
using std::list;

struct ParametersList {
	list <string> params;

	void Add (const string & param);
};

#endif

