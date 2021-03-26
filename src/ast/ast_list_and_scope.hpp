#ifndef ast_list_and_scope_hpp
#define ast_list_and_scope_hpp
/*
class List : public Expression{
    private:
        std::vector<ExpressionPtr> exprs;
        std::string type;
    public:
        List() {};
        
        virtual void pushexpr(ExpressionPtr _expr) override{
            exprs.push_back(_expr);
        }

        virtual void put_type(std::string _type) override{
            type = _type;
        }

        virtual std::string get_type() override{
           return type;
        }

        virtual void getGlobal(std::vector<std::string> &v) {
            for (int i = 0; i < exprs.size(); i++) {
                if (exprs[i]){
                    exprs[i]->getGlobal(v);
                }
            }
        }

        virtual void codegen(Table &head, std::ostream &dst) override{
            assert(exprs.size() != 0);
            dst << "Class List:" << exprs.size() << std::endl;
            for(int i=0; i < exprs.size(); i++){
                if(exprs[i] != NULL){
                    if(dynamic_cast<InitDecl*>(exprs[i])){
                        exprs[i]->put_type(type);
                    }
                    exprs[i]->codegen(head, dst);
                }
            }
        }
        virtual void print(std::ostream &dst) override{
            assert(exprs.size() != 0);
            dst << "Class List:" << exprs.size();
            for(int i=0; i < exprs.size(); i++){
                if(exprs[i] != NULL){
                    exprs[i]->print(dst);
                }
            }
        }
};
*/
class Scope : public Expression{
    private:
        ExpressionPtr declist = NULL;
        ExpressionPtr statlist = NULL;
    public:
    Scope(ExpressionPtr _declist, ExpressionPtr _statlist) :
    declist(_declist),
    statlist(_statlist)
    {}

    Scope(ExpressionPtr _statlist) : 
    statlist(_statlist)
    { }

    virtual void print(std::ostream &dst) override{
        dst << "Class Scope:";
        statlist->print(dst);
    }

    virtual void codegen(Table &head, std::ostream &dst){
        //dst << "Class Scope:" << std::endl;
        if(declist){
            declist->codegen(head,dst);
        }
        if(statlist){
            statlist->codegen(head, dst);
        }
    }

    virtual void pushexpr(ExpressionPtr _expr) override{
        std::cout << "Unimplemented feature" << std::endl;
    }
};

#endif