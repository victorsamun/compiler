%skeleton "lalr1.cc"   
%require "2.4"
%defines
%define parser_class_name "Parser"

%code requires {
	#include <string>
	#include <iostream>
	#include "ast/ast.hpp"
	#include "ast/CodeGeneratorState.hpp"

	class Driver;
}

%parse-param { Driver & driver }
%lex-param   { Driver & driver }

%debug
%error-verbose

%union {
	double dval;
	std::string * sval;
	IASTNode * eval;

	FunctionPrototype * proto;
	ParametersList * plist;
	CallParametersList * cplist;
}

%code {
	#include "driver.hpp"
}

%start program

%token	END	0
%token	PLUS MINUS MULT DIV
%token	NOT AND OR XOR IMPL EQUIV
%token	B_TRUE B_FALSE
%token	LP RP LB RB
%token	ASSIGN RETURN
%token	CMPL CMPLE CMPG CMPGE CMPEQ CMPNE
%token	IF THEN ELSE
%token	WHILE DO
%token	SUBPROGRAM EXTERN
%token	STARTBLOCK ENDBLOCK
%token	SEMICOLON COLON
%token	READ WRITE
%token	<sval>	IDENTIFIER
%token	<dval>	NUMBER

%type	<eval>	program statement definition external expression expression1 expression2
%type	<eval>	arithmetic_expression compare_expression boolean_expression call_expression assign_expression
%type	<eval>	statements_list expressions_list
%type	<proto>	prototype
%type	<plist>	params_list params_list1
%type	<cplist>expressions_enum expressions_enum1

%destructor { delete $$; } IDENTIFIER;
%destructor { delete $$; } program;

%%

program
	:	statements_list 
		{
			CodeGeneratorState state;

			$$ = new ProgramNode ($1);
			$$->GenerateCode (state);
		}
	;

statements_list
	:	statements_list SEMICOLON statement
		{
			(static_cast <ASTNodesListNode *> ($1))->Add ($3);
			$$ = $1;
		}
	|	statement
		{
			ASTNodesListNode * result = new ASTNodesListNode ();
			result->Add ($1);
			$$ = result;
		}
	;

expressions_list
	:	expressions_list SEMICOLON expression
		{
			(static_cast <ASTNodesListNode *> ($1))->Add ($3);
			$$ = $1;
		}
	|	expression
		{
			ASTNodesListNode * result = new ASTNodesListNode ();
			result->Add ($1);
			$$ = result;
		}
	;

statement
	:	definition
	|	external
	|	/* Nothing */
		{
			$$ = NULL;
		}
	;

definition
	:	SUBPROGRAM prototype STARTBLOCK expressions_list ENDBLOCK
		{
			$$ = new FunctionDefinitionNode ($2, static_cast <ASTNodesListNode *> ($4));
		}
	;

prototype
	:	IDENTIFIER LB params_list RB
		{
			$$ = new FunctionPrototype (* $1, $3);
		}
	;

params_list
	:	/* Nothing */
		{
			$$ = new ParametersList ();
		}
	|	params_list1
	;

params_list1
	:	params_list1 COLON IDENTIFIER
		{
			$1->Add (* $3);
			$$ = $1;
		}
	|	IDENTIFIER
		{
			ParametersList * result = new ParametersList ();
			result->Add (* $1);
			$$ = result;
		}
	;

external
	:	EXTERN prototype
		{
			$$ = new ExternalFunctionNode ($2);
		}
	;

expression
	:	expression1
	|	expression2
	;

expression1
	:	assign_expression
	|	arithmetic_expression
	|	READ IDENTIFIER
		{
			$$ = new ReadNode (* $2);
		}
	|	WRITE arithmetic_expression
		{
			$$ = new WriteNode ($2);
		}
	|	RETURN arithmetic_expression
		{
			$$ = new ReturnNode ($2);
		}
	|	IF boolean_expression THEN expression1 ELSE expression1
		{
			$$ = new IfThenElseNode ($2, $4, $6);
		}
	|	STARTBLOCK expressions_list ENDBLOCK
		{
			$$ = $2;
		}
	|	WHILE boolean_expression DO expression1
		{
			$$ = new WhileDoNode ($2, $4);
		}
	;

expression2
	:	IF boolean_expression THEN expression
		{
			$$ = new IfThenElseNode ($2, $4, NULL);
		}
	|	IF boolean_expression THEN expression1 ELSE expression2
		{
			$$ = new IfThenElseNode ($2, $4, $6);
		}
	;

expressions_enum
	:	/* Nothing */
		{
			$$ = new CallParametersList ();
		}
	|	expressions_enum1
	;

expressions_enum1
	:	expressions_enum1 COLON expression
		{
			$1->Add ($3);
			$$ = $1;
		}
	|	expression
		{
			CallParametersList * result = new CallParametersList ();
			result->Add ($1);
			$$ = result;
		}
	;

call_expression
	:	IDENTIFIER LP expressions_enum RP
		{
			$$ = new FunctionCallNode (* $1, $3);
		}
	;

assign_expression
	:	IDENTIFIER ASSIGN arithmetic_expression
		{
			$$ = new AssignOperationNode (* $1, $3);
		}
	;

%left PLUS MINUS;
%left MULT DIV;

arithmetic_expression
	:	arithmetic_expression PLUS arithmetic_expression
		{
			$$ = new PlusOperationNode ($1, $3);
		}
	|	arithmetic_expression MINUS arithmetic_expression
		{
			$$ = new MinusOperationNode ($1, $3);
		}
	|	arithmetic_expression MULT arithmetic_expression
		{
			$$ = new MultiplicationOperationNode ($1, $3);
		}
	|	arithmetic_expression DIV arithmetic_expression
		{
			$$ = new DivisionOperationNode ($1, $3);
		}
	|	LP arithmetic_expression RP
		{
			$$ = $2;
		}
	|	call_expression
	|	IDENTIFIER
		{
			$$ = new VariableNode (* $1);
		}
	|	NUMBER
		{
			$$ = new NumberNode ($1);
		}
	;

%left AND;
%left OR;
%left XOR IMPL EQUIV;
%left NOT;

boolean_expression
	:	NOT boolean_expression
		{
			$$ = new NotOperationNode ($2);
		}
	|	boolean_expression AND boolean_expression
		{
			$$ = new AndOperationNode ($1, $3);
		}
	|	boolean_expression OR boolean_expression
		{
			$$ = new OrOperationNode ($1, $3);
		}
	|	boolean_expression XOR boolean_expression
		{
			$$ = new XorOperationNode ($1, $3);
		}
	|	boolean_expression IMPL boolean_expression
		{
			$$ = new OrOperationNode (new NotOperationNode ($1), $3);
		}
	|	boolean_expression EQUIV boolean_expression
		{
			$$ = new NotOperationNode (new XorOperationNode ($1, $3));
		}
	|	LP boolean_expression RP
		{
			$$ = $2;
		}
	|	compare_expression
	|	B_TRUE
		{
			$$ = new TrueNode ();
		}
	|	B_FALSE
		{
			$$ = new FalseNode ();
		}
	;

compare_expression
	:	arithmetic_expression CMPL arithmetic_expression
		{
			$$ = new LessOperatorNode ($1, $3);
		}
	|	arithmetic_expression CMPLE arithmetic_expression
		{
			$$ = new LessEqualsOperatorNode ($1, $3);
		}
	|	arithmetic_expression CMPG arithmetic_expression
		{
			$$ = new GreaterOperatorNode ($1, $3);
		}
	|	arithmetic_expression CMPGE arithmetic_expression
		{
			$$ = new GreaterEqualsOperatorNode ($1, $3);
		}
	|	arithmetic_expression CMPEQ arithmetic_expression
		{
			$$ = new EqualsOperatorNode ($1, $3);
		}
	|	arithmetic_expression CMPNE arithmetic_expression
		{
			$$ = new NotEqualsOperatorNode ($1, $3);
		}
	;

%%

void
yy::Parser::error (
	const yy::location & l,
	const std::string & m)
{
	driver.error (m);
}

