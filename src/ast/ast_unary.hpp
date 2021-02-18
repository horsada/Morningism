#ifndef ast_unary_hpp
#define ast_unary_hpp

#include "ast_expression.hpp"

class Unary : public Expression 
{
    private:
        std::shared_ptr<Expression> right;
        std::shared_ptr<std::string> op;
    public:
        Unary(std::shared_ptr<std::string> _op, std::shared_ptr<Expression> _right) :
            right(_right);
            op(_op);
        { }
};

#endif