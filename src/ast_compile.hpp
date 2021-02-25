#ifndef ast_compile_hpp
#define ast_compile_hpp

#include "codegen/table.hpp"
#include "ast.hpp"

void CompileRec(std::string destReg, ExpressionPtr arg1, Expression op, ExpressionPtr arg2); // Convert ast to 3AC

void Compile(ExpressionPtr ast); // main function

std::string newtemp(); // return fresh temp name on each invocation, e.g. t1, t2

#endif