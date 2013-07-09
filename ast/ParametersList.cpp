#include "ParametersList.hpp"
#include <string>

using std::string;

void ParametersList::Add (const string & param) {
	this->params.push_back (param);
}

