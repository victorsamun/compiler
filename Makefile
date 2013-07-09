.PHONY: Build Lexer Parser

Build: Parser Lexer
	g++ -Ilib -o bin/compiler ast/*.cpp lexer.cpp parser.cpp driver.cpp compiler.cpp `llvm-config --cppflags --ldflags --libs` -ldl
	rm lexer.cpp location.hh parser.cpp parser.hpp position.hh stack.hh

Lexer: lexer.l
	flex -o lexer.cpp lexer.l 

Parser: parser.y
	bison -d -o parser.cpp parser.y

