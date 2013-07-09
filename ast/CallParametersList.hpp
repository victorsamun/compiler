#ifndef _CALL_PARAMETERS_LIST_HPP_
#define _CALL_PARAMETERS_LIST_HPP_

#include <list>
#include "IASTNode.hpp"
#include "shared_ptr.hpp"

using std::list;

class CallParametersList {
	list <shared_ptr <IASTNode> > params;

public:
	void Add (IASTNode * param);

	list <shared_ptr <IASTNode> >::const_iterator begin (void) const;
	list <shared_ptr <IASTNode> >::const_iterator end (void) const;
	size_t size (void) const;
};

#endif

