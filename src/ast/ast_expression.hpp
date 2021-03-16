#ifndef ast_expression_hpp
#define ast_expression_hpp

class Expression;
typedef Expression* ExpressionPtr;

class Expression{
    public:
        virtual void print(std::ostream &dst) const{
            std::cout << "test";
        }
        
        //virtual void pushexpr(ExpressionPtr _expr);
};

#endif