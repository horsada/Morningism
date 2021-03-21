#ifndef ast_other_classes_hpp
#define ast_other_classes_hpp

class FunctionCall : public Expression{
    public:
        FunctionCall(ExpressionPtr _postfix, ExpressionPtr _args) 
        {}

        virtual void print(std::ostream &dst) override{
            std::cout << "Class FunctionCall: Unimplemented feature";
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            std::cout << "Unimplemented feature";
        }
};

class PostFixOp : public Expression{
    public:
        PostFixOp(ExpressionPtr _postfix, std::string* _op) 
        {}

        virtual void print(std::ostream &dst) override{
            std::cout << "Class PostFixOp: Unimplemented feature";
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            std::cout << "Unimplemented feature";
        }
};

class AssignOp : public Expression{
    private:
        ExpressionPtr unary;
        std::string op;
        ExpressionPtr assign;
    public:
        AssignOp(ExpressionPtr _unary, std::string* _op, ExpressionPtr _assign) :
        unary(_unary),
        op(*_op),
        assign(_assign)
        {delete _op;}

        virtual void print(std::ostream &dst) override{
            std::cout << "Class AssignOp: Unimplemented feature";
            unary->print(dst);
            dst << op;
            assign->print(dst);
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            std::cout << "Unimplemented feature";
        }
};

class Decl : public Expression{
    private:
        std::string decl_spec;
        ExpressionPtr init_decl_list;
    public:
        Decl(std::string* _decl_spec, ExpressionPtr _init_decl_list) :
        decl_spec(*_decl_spec),
        init_decl_list(_init_decl_list)
        {delete _decl_spec;}

        std::string getid(){
            return decl_spec;
        }

        virtual void print(std::ostream &dst) override{
            assert(init_decl_list != NULL);
            dst << "Class Decl";
            //dst << getid();
            init_decl_list->print(dst);
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            dst << "Class Decl:";
            init_decl_list->codegen(dst);
        }
};

class DirectDecl : public Expression{
    private:
        ExpressionPtr direct_decl;
        ExpressionPtr param_type_list = NULL;
    public:
        DirectDecl(ExpressionPtr _direct_decl, ExpressionPtr _param_type_list) :
        direct_decl(_direct_decl),
        param_type_list(_param_type_list)
        {}

        virtual void print(std::ostream &dst) override{
            assert(param_type_list == NULL); // debugging
            dst << "Class DirectDecl:";
            direct_decl->print(dst);
            //param_type_list->print(dst);
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            dst << "Class DirectDecl:";
            direct_decl->print(dst);
        }
};

class InitDecl : public Expression{
    private:
        ExpressionPtr decl;
        ExpressionPtr initialiser;
    public:
        InitDecl(ExpressionPtr _decl, ExpressionPtr _initialiser) :
        decl(_decl),
        initialiser(_initialiser)
        {}

        virtual void print(std::ostream &dst) override{
            dst << "Class: Init Decl" << std::endl;
            assert(initialiser != NULL); // debugging
            if(initialiser != NULL){
                decl->print(dst);
                initialiser->print(dst);
            }
            else{
                decl->print(dst);
            }
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            dst << "Init Decl:";
            if(dynamic_cast<Variable*>(decl)){
                std::string var = decl->getvar();
                int32_t val = 0;
                if(dynamic_cast<IntConst*>(initialiser)){
                    val = initialiser->getint();
                    dst << "\t.globl  " << var << "\n" << "\t.data\n"
                    << "\t.align  2\n" << "\t.type   " << var << ", @object\n"
                    << "\t.size   " << var << ", 4\n" << var << ":\n"
                    << "\t.word " << val << "\n";
                }
            }
        }
};

class ParamDecl : public Expression{
    private:
        std::string decl_spec;
        ExpressionPtr init_decl_list;
    public:
        ParamDecl(std::string* _decl_spec, ExpressionPtr _init_decl_list) :
        decl_spec(*_decl_spec),
        init_decl_list(_init_decl_list)
        {delete _decl_spec;}

        virtual void print(std::ostream &dst) override{
            std::cout << "class ParamDecl: Unimplemented feature";
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            std::cout << "Unimplemented feature";
        }
};

class IDList : public Expression{
    private:
        std::vector<std::string> id_list;
    public:
        IDList(std::string* _id){
            id_list.push_back(*_id);
            delete _id;
        }

        IDList(){}
        virtual void print(std::ostream &dst) override{
            std::cout << "class IDList: Unimplemented feature";
        }
        
        virtual void pushexpr(std::string* _id){
            id_list.push_back(*_id);
            delete _id;
        }

        virtual void codegen(std::ostream &dst){
            std::cout << "Unimplemented feature";
        }
};
/*
class DeclSpec : public Expression{
    private:
        std::string type_spec;
        std::string init_decl_list = NULL;
    public:
        DeclSpec(std::string* _decl_spec, std::string* _init_decl_list) :
        type_spec(*_decl_spec),
        init_decl_list(*_init_decl_list)
        {delete _decl_spec;
            delete _init_decl_list;}

        std::string getid(){
            return type_spec;
        }

        virtual void print(std::ostream &dst) override{
            //assert(init_decl_list != NULL);
            dst << "Class DeclSpec";
            //dst << getid();
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(std::ostream &dst){
            std::cout << "Unimplemented feature";
        }
};
*/
#endif