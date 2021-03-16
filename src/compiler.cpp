#include "ast/ast.hpp"

int main(){
    ExpressionPtr ast = parseAST();
    ast->print(std::cout);
    std::cout << std::endl;

    return 0;
}