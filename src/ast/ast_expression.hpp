#ifndef ast_expression_hpp
#define ast_expression_hpp

class Expression;
typedef Expression* ExpressionPtr;

class Expression{
    public:

    virtual ~Expression()
    {}
        virtual void print(std::ostream &dst) {
            std::cout << "Class Expression: Unimplemented feature";
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            std::cout << "Unimplemented feature";
        }

        virtual void pushexpr(std::string* id){
            std::cout << "Unimplemented feature";
        }
};

#endif