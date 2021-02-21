#ifndef ast_if_hpp
#define ast_if_hpp

class If : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    protected:
        If(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}
};

class IfElse : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr mid;
        ExpressionPtr right;
    protected:
        IfElse(ExpressionPtr _left, ExpressionPtr _mid, ExpressionPtr _right) : 
            left(_left),
            mid(_mid),
            right(_right)
        {}
};

class Switch : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    protected:
        Switch(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}
};

#endif