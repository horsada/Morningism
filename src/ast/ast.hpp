#ifndef ast_hpp
#define ast_hpp

#include <memory>
#include <string>
#include <map>
#include <cassert>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <stack>

std::string newlabel();

std::string newtreg();

std::string newsreg();

#include "ast_expression.hpp"
#include "ast_bin_op.hpp"
#include "ast_unary.hpp"
#include "ast_conditional.hpp"
#include "ast_table.hpp"
#include "ast_translation.hpp"
#include "ast_types.hpp"
#include "ast_function.hpp"
#include "ast_variable.hpp"
#include "ast_loop.hpp"
#include "ast_lol.hpp"
#include "ast_list_and_scope.hpp"
#include "ast_other_classes.hpp"

extern ExpressionPtr parseAST(std::string src);

#endif