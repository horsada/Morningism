# Language Processing - C to MIPS Compiler
## By Adam Horsler, Varun Srivastava

# Usage
- The main function takes as arguments an input file, which is a subset of the C language (as detailed above). The output file will be the corresponding MIPS 1 ISA assembly.
- The compiler is heavily unoptimised, producing code similar to a GCC -0 optimisation. 

# Functionality

## 1. Lexing
- The lexing section of the compiler was written using Flex, found in the **lexer.flex** file. The input file is tokenised before being sent to the parser for parsing. 

## 2. Parsing
- Parsing was done using Bison. The Bison parser is a bottom-up parser, using the grammar defined in the **parser.y** file. 

## 3. Abstract Syntax Tree (AST)
- Upon parsing the input tokens, the AST is populated.
- The AST is created using an OOP approach, with a top-level _Expression_ class that the tree starts from. 
- Each derived class from the _Expression_ class contains a _mips_ member function that outputs the corresponding MIPS assembly of that class.
- The tree is left-traversed to output the MIPS assembly in the correct order.

## 4. Stack
- Currently, the assembly is configured to send all local variables to memory, making minimal use of the MIPS temporary registers. 
  - This was done for simplicity and for easier debugging/testing. 

# Future Work
- Optimise the output to make better use of temporary registers.
- Add functionality for the current un-supported C things. 
