#include "ast/ast.hpp"

int main(){
    const ExpressionPtr ast = parseAST();
    ast->print(std::cout);
    std::cout << std::endl;

    return 0;
}