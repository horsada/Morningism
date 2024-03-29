CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS += -std=c++11 -W -Wall -g -s -Wno-unused-parameter
CFLAGS += -I include

all: bin/c_compiler

src/parser.tab.cpp src/parser.tab.hpp: src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp: src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp src/lexer.flex

bin/c_compiler: src/compiler.o src/parser.tab.o src/lexer.yy.o 
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/c_compiler $^

#bin/c_mips: 
#	mkdir -p bin
#	mips64-linux-gnuabi64-gcc src/test.c -static -g3

clean:
	rm src/*.o
	rm src/*.tab.cpp
	rm src/*.yy.cpp
	rm -R bin/
	rm -r src/parser.output
	rm -r src/parser.tab.hpp