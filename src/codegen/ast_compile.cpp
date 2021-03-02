
std::string newreg(){
    static int count = 0;
    std::string dest = "$" + std::to_string(count);
    count++;
    return dest;
}

ExpressionPtr traverseleft(Expression expr){
    auto cur = std::make_shared<Expression>(expr);
    return cur;
}

void CompileRec(Expression expr, Table head){
    std::string dest = newreg();
    if(head.checkentry(expr)){
        std::cout << dest << " := " << head.getentry(expr) << std::endl;
    }
    else{
        
    }
}
