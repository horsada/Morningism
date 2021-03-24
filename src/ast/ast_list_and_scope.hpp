#ifndef ast_list_and_scope_hpp
#define ast_list_and_scope_hpp

class List : public Expression{
    private:
        std::vector<ExpressionPtr> exprs;
    public:
        List() {};
        
        virtual void pushexpr(ExpressionPtr _expr) override{
            exprs.push_back(_expr);
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
            for(int i=0; i < exprs.size(); i++){
                if(exprs[i] != NULL){
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
        dst << "Class Scope:" << std::endl;
        statlist->codegen(head, dst);
    }

    virtual void pushexpr(ExpressionPtr _expr) override{
        std::cout << "Unimplemented feature" << std::endl;
    }
};

#endif