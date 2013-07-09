#include <iostream>
#include "driver.hpp"

Driver::Driver (void) :
	trace_scanning (false), trace_parsing (false) { }

Driver::~Driver (void) { }

void Driver::parse (const std::string & filename_) {
	filename = filename_;
	scan_begin ();
	yy::Parser parser (* this);
	parser.set_debug_level (trace_parsing);
	parser.parse ();
	scan_end ();
}

void Driver::error (const std::string & m) {
	std::cerr << m << std::endl;
}
