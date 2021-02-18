CPPFLAGS += -W -Wall -g 

# This avoids error: ‘fileno’ was not declared in this scope
CPPFLAGS += -std=c++0x

# Avoid warnings about yyunput not used
CPPFLAGS += -Wno-unused-function

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
    	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex
		flex -o src/lexer.yy.cpp src/lexer.flex

clean : 
		rm src/*.o
		rm src/*.yy.cpp
		rm src/*tab.cpp

