CPPFLAGS += -W -Wall -g 

# This avoids error: ‘fileno’ was not declared in this scope
CPPFLAGS += -std=c++0x

# Avoid warnings about yyunput not used
CPPFLAGS += -Wno-unused-function

all : 

lexer.yy.cpp : lexer.flex
	flex -o lexer.yy.cpp lexer.yy.o

clean : 
	-rm -f 
	-rm -f *.yy.cpp