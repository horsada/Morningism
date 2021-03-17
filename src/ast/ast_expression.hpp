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

        virtual void codegen(std::ostream &dst);

        virtual std::string getid();
};

#endif