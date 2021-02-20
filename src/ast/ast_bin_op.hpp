#ifndef ast_bin_op_hpp
#define ast_bin_op_hpp

class BinOp : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    protected:
        BinOp(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}
};

class AddOp : public BinOp
{
    public:
        AddOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};


class SubOp : public BinOp
{
    public:
        SubOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};

class MulOp : public BinOp
{
    public:
        MulOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};

class DivOp : public BinOp
{
    public:
        DivOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};

class EqualToOp : public BinOp
{
    public:
        EqualToOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};

class NotEqualToOp : public BinOp
{
    public:
        NotEqualToOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};

class LessThanOp : public BinOp
{
    public:
        LessThanOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};

class GreaterThanOp : public BinOp
{
    public:
        GreaterThanOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
};

#endif