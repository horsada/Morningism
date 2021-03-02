#ifndef ast_compile_hpp
#define ast_compile_hpp

#include "codegen/table.hpp"
#include "ast.hpp"
#include <typeinfo>

void CompileRec(Expression expr, Table head); // Convert ast to 3AC

void Compile(ExpressionPtr ast); // main function

std::string newtemp(); // return fresh temp name on each invocation, e.g. t1, t2

#endif