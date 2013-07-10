%{
	#include <iostream>
	#include <cstdlib>
	#include "parser.hpp"
	#include "driver.hpp"

	typedef yy::Parser::token token;

	#define yyterminate() return token::END
%}

%option noyywrap
%option debug

num	[0-9]
hnum	[0-9a-fA-F]
char	[a-zA-Z_]
nchar	[a-zA-Z_0-9]
ws	[ \t]
nl	[\r\n]

%%

"+"	return token::PLUS;
"-"	return token::MINUS;
"*"	return token::MULT;
"/"	return token::DIV;

"<"	return token::CMPL;
"<="	return token::CMPLE;
">"	return token::CMPG;
">="	return token::CMPGE;
"=="	return token::CMPEQ;
"<>"	return token::CMPNE;

"!"	return token::NOT;
"&&"	return token::AND;
"||"	return token::OR;
"^"	return token::XOR;
"=>"	return token::IMPL;
"~~"	return token::EQUIV;

"true"	return token::B_TRUE;
"false"	return token::B_FALSE;

"if"	return token::IF;
"->"	return token::THEN;
"|"	return token::ELSE;

"while"	return token::WHILE;
"do"	return token::DO;

"("	return token::LP;
")"	return token::RP;

"["	return token::LB;
"]"	return token::RB;

"sub"	return token::SUBPROGRAM;
"load"	return token::EXTERN;
"ret"	return token::RETURN;

"{"	return token::STARTBLOCK;
"}"	return token::ENDBLOCK;

"="	return token::ASSIGN;
";"	return token::SEMICOLON;
","	return token::COLON;

"=>>"	return token::READ;
"<<="	return token::WRITE;

{char}{nchar}*	{
		yylval->sval = new std::string (yytext);
		return token::IDENTIFIER;
	}

[+-]?(?:(?:{num}+|{num}*\.{num}+)(?:[eE][+-]?{num}+)?|0[xX](?:{hnum}+|{hnum}*\.{hnum}+)(?:[pP]{num}+)?|(?i:INFINITY|INF)|NAN(?:\({nchar}+\))?)	{
		yylval->dval = std::atof (yytext);
		return token::NUMBER;
	}

({nl}|{ws})+	/* ignore */
.	{
		driver.error ("invalid character");
	}

%%

void Driver::scan_begin (void) {
	yy_flex_debug = trace_scanning;
	if (filename == "-")
		yyin = stdin;
	else if (! (yyin = fopen (filename.c_str (), "r"))) {
		error (std::string ("cannot open ") + filename);
		exit (EXIT_FAILURE);
	}
}

void Driver::scan_end (void) {
	fclose (yyin);
}

