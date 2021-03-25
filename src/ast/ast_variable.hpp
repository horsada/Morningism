#ifndef ast_variable_hpp
#define ast_variable_hpp

class Variable : public Expression{
    private:
        std::string var;
        std::string type = "";
    public:
        Variable(std::string* _var) :
        var(*_var)
        { delete _var; }

        virtual void print(std::ostream &dst) override{
            dst << "Class Variable" /*getvar()*/;
        }

        std::string getvar(){
            return var;
        }
        virtual void codegen(Table &head, std::ostream &dst) override{
            dst << "Class Variable:" << getvar() << std::endl;
        }

        virtual void function_var(Table &head) override{
            head.putfunction(getvar());
        }
};



#endif