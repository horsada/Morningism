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

        virtual void codegen(std::ostream &dst) override{
            for(int i=0; i < exprs.size(); i++){
                if(exprs[i]){
                    exprs[i]->codegen(dst);
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

        virtual void codegen(std::ostream &dst){
            statlist->codegen(dst);
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif