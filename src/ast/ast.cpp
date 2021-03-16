#include "ast.hpp"

std::string newreg(){
    static int count = 0;
    std::string dest = "$" + std::to_string(count);
    count++;
    return dest;
}

ExpressionPtr traverseleft(ExpressionPtr expr){
    ExpressionPtr cur = expr;
    return cur;
}
/*
void CompileRec(Expression expr, Table head){
    std::string dest = newreg();
    if(head.checkentry(expr)){
        //std::cout << dest << " := " << head.getentry(expr) << std::endl;
    }
    else{
        
    }
}
*/