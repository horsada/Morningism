#include "ast/ast.hpp"

int main(int argc, char* argv[]){
    std::string input_file = argv[1];
    ExpressionPtr ast = parseAST(input_file);
    ast->print(std::cout);
    std::cout << std::endl;

    return 0;
}