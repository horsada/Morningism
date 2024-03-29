#ifndef translation_hpp
#define translation_hpp

class TranslationUnit : public Expression{
    private:
        std::vector<ExpressionPtr> exprs;
    public:
        TranslationUnit(ExpressionPtr _expr){
            exprs.push_back(_expr);
        }
        
        TranslationUnit() {};

        void pushexpr(ExpressionPtr _expr){
            exprs.push_back(_expr);
        }

        virtual void print(std::ostream &dst) override{
            assert(exprs.size() != 0);
            dst << "Class TranslationUnit";
            for(int i=0; i < exprs.size(); i++){
                if(exprs[i] != nullptr){
                    dst << exprs.size();
                    exprs[i]->print(dst);
                }
                else{
                    std::cerr << "nullptr" << std::endl;
                }
            }
        }

        virtual void codegen(Table &head, std::ostream &dst) override{
            //assert(exprs.size() != 0);
            //dst << "Class TranslationUnit" << std::endl;
            for(int i=0; i < exprs.size(); i++){
                if(exprs[i] != nullptr){
                    exprs[i]->codegen(head, dst);
                }
                else{
                    std::cerr << "nullptr" << std::endl;
                }
            }
        }
};

#endif