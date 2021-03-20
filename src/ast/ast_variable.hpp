#ifndef ast_variable_hpp
#define ast_variable_hpp

class Variable : public Expression{
    private:
        std::string* var;
    public:
        Variable(std::string* _var) :
        var(_var)
        { }
        /*
        ~Variable(){
            delete var;
        }
        */
        virtual void print(std::ostream &dst) override{
            dst << "Class Variable";
        }

        std::string getvar(){
            return *var;
        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }
};



#endif