#ifndef ast_other_classes_hpp
#define ast_other_classes_hpp

class FunctionCall : public Expression{
    private:
        ExpressionPtr postfix;
        ExpressionPtr args = NULL;
    public:
        FunctionCall(ExpressionPtr _postfix, ExpressionPtr _args) :
        postfix(_postfix),
        args(_args)
        {}

        virtual void print(std::ostream &dst) override{
            std::cout << "Class FunctionCall: Unimplemented feature";
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(Table &head, std::ostream &dst){
            dst << "Class FunctionCall:";
            dst << "Unimplemented feature";
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

        virtual void codegen(Table &head, std::ostream &dst){
            std::cout << "Class PostFixOp: Unimplemented feature";
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

        void getGlobal(std::vector<std::string> &v) {
            init_decl_list->getGlobal(v);
            }

        virtual void print(std::ostream &dst) override{
            dst << "Class Decl:";
            dst << getvar();
            init_decl_list->print(dst);
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(Table &head, std::ostream &dst){
            dst << "Class Decl:\n";
            init_decl_list->codegen(head, dst);
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

        void getGlobal(std::vector<std::string> &v) {
            if (dynamic_cast<Variable*>(direct_decl)){
            v.push_back(direct_decl->getvar());
            }
        }

        virtual void print(std::ostream &dst) override{
            dst << "Class DirectDecl:";
            direct_decl->print(dst);
            //param_type_list->print(dst);
        }
        
        virtual void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature";
        }

        virtual void codegen(Table &head, std::ostream &dst){
            dst << "Class DirectDecl:\n";
            direct_decl->codegen(head, dst);
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

        void getGlobal(std::vector<std::string> &v){
            if (dynamic_cast<Variable *>(decl)){
                v.push_back(decl->getvar());
            }
        }

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

        virtual void codegen(Table &head, std::ostream &dst){
            dst << "Init Decl:\n";
            head.add_total_offset(-4);
            int offset = head.get_total_offset();
            dst << "\taddiu\t$sp\t$sp\t" << -4 << std::endl;

            std::string t_reg = head.newtreg();
            if(dynamic_cast<Variable*>(decl)){
                std::string var = decl->getvar();
                head.insert_stack_offset(var, offset);
                head.insert_reg(var, t_reg);
                if(dynamic_cast<IntConst*>(initialiser)){
                    int val = initialiser->getint();
                    /*dst << "\t.globl  " << var << "\n" << "\t.data\n"
                    << "\t.align  2\n" << "\t.type   " << var << ", @object\n"
                    << "\t.size   " << var << ", 4\n" << var << ":\n"
                    << "\t.word " << val << "\n";*/
                    dst << "\tli\t" << t_reg << "\t" << val << std::endl; 
                    dst << "\tsw\t" << t_reg << "\t" << "0($sp)" << std::endl;
                }
                if(dynamic_cast<BinOp*>(initialiser)){
                initialiser->codegen(head, dst);
                std::string dest_reg = initialiser->getdestreg();
                head.insert_stack_offset(decl->getvar(), head.get_total_offset());
                dst << "\tsw\t" << dest_reg << "\t" << "0($sp)" << std::endl;
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

        virtual void codegen(Table &head, std::ostream &dst){
            std::cout << "Class ParamDecl: Unimplemented feature";
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

        virtual void codegen(Table &head, std::ostream &dst){
            std::cout << "Class IDList: Unimplemented feature";
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