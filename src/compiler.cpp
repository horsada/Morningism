#include "ast/ast.hpp"

int main(int argc, char const *argv[]){
    if(argc < 3){
        fprintf(stderr, "usage : compiler sourceCode\n");
        exit(1);
    }

    std::ifstream out(argv[2]);
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    std::string src(argv[1]);

    ExpressionPtr ast = parseAST(src);
    std::cout << src << std::endl;
    ast->codegen(std::cout);
    std::cout << std::endl;

    return 0;
}