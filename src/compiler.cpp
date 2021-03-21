#include "ast/ast.hpp"

Table head;

int main(){
    /*if(argc < 3){
        fprintf(stderr, "usage : compiler sourceCode\n");
        exit(1);
    }*/
    /*
    std::ifstream out(argv[2]);
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    */

    std::string src = "unused";
    ExpressionPtr ast = parseAST(src);
    std::cout << "*---------------------PARSED CONTENT-----------------*" << std::endl;
    ast->codegen(std::cout);
    std::cout << std::endl;

    return 0;
}