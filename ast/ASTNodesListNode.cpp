#include "ASTNodesListNode.hpp"
#include "indent.hpp"
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::list;
using std::for_each;
using std::bind2nd;
using std::mem_fun;

void ASTNodesListNode::Add (IASTNode * expr) {
	if (expr)
		this->exprs.push_back (expr);
}

void ASTNodesListNode::Print (size_t indent) const {
	print_indent (indent);
	cout << '{' << endl;

	for (list <shared_ptr <IASTNode> >::const_iterator it = this->exprs.begin (); it != this->exprs.end (); ++ it) {
		(* it)->Print (indent + 1);
		cout << ';' << endl;
	}

	print_indent (indent);
	cout << '}';
}

Value * ASTNodesListNode::GenerateCode (CodeGeneratorState & state) const {
	for_each (this->exprs.begin (), this->exprs.end (), bind2nd (mem_fun (& IASTNode::GenerateCode), state));
}

