#ifndef ast_if_hpp
#define ast_if_hpp

class If : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        If(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}

        virtual void print(std::ostream &dst) override{
            dst << "Class If:";
            left->print(dst);
            right->print(dst);
        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class IfElse : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr mid;
        ExpressionPtr right;
    public:
        IfElse(ExpressionPtr _left, ExpressionPtr _mid, ExpressionPtr _right) : 
            left(_left),
            mid(_mid),
            right(_right)
        {}
        virtual void print(std::ostream &dst) override{
            dst << "Class IfElse:";
            left->print(dst);
            right->print(dst);
        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class Switch : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        Switch(ExpressionPtr _left, ExpressionPtr _right) : 
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