#include "CallParametersList.hpp"

void CallParametersList::Add (IASTNode * param) {
	this->params.push_back (param);
}

list <shared_ptr <IASTNode> >::const_iterator CallParametersList::begin (void) const {
	return this->params.begin ();
}

list <shared_ptr <IASTNode> >::const_iterator CallParametersList::end (void) const {
	return this->params.end ();
}

size_t CallParametersList::size (void) const {
	return this->params.size ();
}

