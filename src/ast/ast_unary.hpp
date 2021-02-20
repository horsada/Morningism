#ifndef ast_unary_hpp
#define ast_unary_hpp

#include "ast_expression.hpp"

class Unary : public Expression 
{
    private:
        ExpressionPtr thing;
    protected:
        Unary(ExpressionPtr _thing) :
            thing(_thing)
        { }
};

class IncrementUnary : public Unary
{
    public:
        IncrementUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
};

class DecrementUnary : public Unary
{
    public:
        DecrementUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
};

class NegUnary : public Unary
{
    public:
        NegUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
};

class NotUnary : public Unary
{
    public:
        NotUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
};

class AddrUnary : public Unary
{
    public:
        AddrUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
};

class SizeofUnary : public Unary
{
    public:
        SizeofUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
};

#endif
