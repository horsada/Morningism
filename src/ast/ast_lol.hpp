#ifndef ast_lol_hpp
#define ast_lol_hpp

class Jump : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        Jump(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}
        
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class Return : public Expression
{
    private:
        ExpressionPtr right;
    public:
        Return(ExpressionPtr _right) : 
            right(_right)
        {}       

        virtual void print(std::ostream &dst) override{
            dst << "Class Return:";
            right->print(dst);
        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Class Return:" << std::endl;
            if(right){
                right->codegen(dst);
                dst << "\tmove\t$2,\t" << /* retReg */ "$ra" << std::endl;
            }
            else{
                dst << "\tb\t\n" << "\tnop\n";
            }
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class GoTo : public Expression
{
    private:
        std::string* label;
    public:
        GoTo(std::string* _label) : 
            label(_label)
        {}
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }      

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};


class Continue : public Expression
{
    private:
        std::string* label;
    public:
        Continue(){

        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }

        void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature" << std::endl;
        }
};


class Break : public Expression
{
    private:
        std::string* label;
    public:
        Break(){
            
        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        } 

        void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif