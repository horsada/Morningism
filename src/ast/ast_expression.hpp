#ifndef ast_expression_hpp
#define ast_expression_hpp

class Expression;
typedef std::shared_ptr<Expression> ExpressionPtr;

class Expression{
    public:
        virtual void print(std::ostream &dst) const =0;
};

#endif