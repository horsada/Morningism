#ifndef ast_variable_hpp
#define ast_variable_hpp

class Variable : public Expression{
    private:
        std::string* var;
    public:
        Variable(std::string *_var) :
        var(_var)
        {}

        virtual void print(std::ostream &dst) const override{
            dst << *var;
        }

        std::string getvar(){
            return *var;
        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};



#endif