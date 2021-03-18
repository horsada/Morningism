#ifndef ast_loop_hpp
#define ast_loop_hpp

class For : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        For(ExpressionPtr _left, ExpressionPtr _right, ExpressionPtr iterator, ExpressionPtr statement) : 
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

class While : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        While(ExpressionPtr _left, ExpressionPtr _right) : 
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

#endif