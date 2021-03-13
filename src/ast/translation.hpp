#ifndef translation_hpp
#define translation_hpp

class TranslationUnit{
    private:
        std::vector<ExpressionPtr> exprs;
    public:
        TranslationUnit(ExpressionPtr _expr){
            exprs.push_back(_expr);
        }  
        void pushexpr(ExpressionPtr expr){
            exprs.push_back(expr);
        }

        virtual void print(){
            for(int i=0; i < exprs.size(); i++){
                if(exprs[i] != nullptr){
                    exprs[i]->print(std::cout);
                }
                else{
                    std::cerr << "nullptr" << std::endl;
                }
            }
        }

};

#endif