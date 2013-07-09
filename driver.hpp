#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <list>
#include "parser.hpp"
#include "ast/ast.hpp"

#define YY_DECL                                 \
    yy::Parser::token_type                      \
    yylex (yy::Parser::semantic_type * yylval,   \
           Driver & driver)
YY_DECL;

class Driver {
public:
	Driver ();
	virtual ~Driver ();

	void scan_begin ();
	void scan_end ();
	bool trace_scanning;

	void parse (const std::string & filename);
	std::string filename;
	bool trace_parsing;

	void error (const std::string & m);
};

#endif
