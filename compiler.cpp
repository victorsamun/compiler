#include <iostream>
#include <cstdlib>
#include "driver.hpp"

int main (int argc, const char * argv []) {
	Driver driver;
	for (++ argv; argv [0]; ++ argv) {
		if (* argv == std::string ("-p"))
			driver.trace_parsing = true;
		else {
			if (* argv == std::string ("-s"))
				driver.trace_scanning = true;
			else
				driver.parse (* argv);
		}
	}

	exit (EXIT_SUCCESS);
}
