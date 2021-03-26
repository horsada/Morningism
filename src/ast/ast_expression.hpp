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

        virtual void put_type(std::string _type){
            //std::cout << "Class Expression: Unimplemented type" << std::endl;
        }

        virtual std::string get_type(){
           //return type;
        }

        virtual void codegen(Table &head, std::ostream &dst){
            dst << "Class Expression: Unimplemented codegen";
        }

        virtual void pushexpr(std::string* id){
            std::cout << "Unimplemented feature";
        }

        virtual std::string getvar(){
            std::cout << "Class Expression: Unimplemented feature";
        }
        
        virtual int32_t getint(){
            std::cout << "Class Expression: Unimplemented feature";
        }

        virtual double getfloat(){
            std::cout << "Class Expression: Unimplemented float\n";
        }

        virtual void getGlobal(std::vector<std::string> &v){
            std::cout << "Class Expression: getglobal unimplemented";
        }

        virtual std::string getdestreg(){
            std::cout << "Unimplemented destReg";
        }

        virtual void function_var(Table &head){
        }

        virtual void codegen(Table &head, std::ostream &dst, std::string arg_reg){
            dst << "Class Expression: Unimplemented arg_reg codegen";
        }
};

#endif