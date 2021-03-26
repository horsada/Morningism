#include "ast/ast.hpp"

Table head;
/*
int main(){
    if(argc < 3){
        fprintf(stderr, "usage : compiler sourceCode\n");
        exit(1);
    }
    
    std::ifstream out(argv[2]);
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    

    std::string src = "unused";
    ExpressionPtr ast = parseAST(src);
    std::cout << "*---------------------PARSED CONTENT-----------------*" << std::endl;
    ast->codegen(head, std::cout);
    //ast->print(std::cout);
    std::cout << std::endl;

    return 0;
}
*/
int main(int argc, char* argv[]){
    if(argc < 4){
        fprintf(stderr, "usage : compiler sourceCode\n");
        exit(1);
    }
    
    std::ofstream out(argv[3]);
    std::string dest = argv[3];
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    std::ifstream in(argv[1]);
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cout to out.txt!

    std::string src = argv[1];
    
    ExpressionPtr ast = parseAST(src);
    std::cout << "*---------------------PARSED CONTENT-----------------*" << std::endl;
    ast->codegen(head, std::cout);
    //ast->print(std::cout);
    std::cout << std::endl;

    return 0;
}
