CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CFLAGS += -I include

all: bin/compiler

src/parser.tab.cpp src/parser.tab.hpp: src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp: src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp src/lexer.flex

bin/compiler: src/compiler.o src/parser.tab.o src/lexer.yy.o 
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/compiler $^

clean:
	rm src/*.o
	rm src/*.tab.cpp
	rm src/*.yy.cpp
	rm -R bin/