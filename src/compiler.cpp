#include "ast/ast.hpp"

int main(int argc, char const *argv[]){
    if(argc < 3){
        fprintf(stderr, "usage : compiler sourceCode\n");
        exit(1);
    }

    std::string src(argv[1]);

    ExpressionPtr ast = parseAST(src);
    ast->print(std::cout);
    std::cout << std::endl;

    return 0;
}