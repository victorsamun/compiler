#include "indent.hpp"
#include <string>
#include <iostream>

using std::cout;
using std::string;

void print_indent (size_t indent) {
	cout << string (indent << 1, ' ');
}
