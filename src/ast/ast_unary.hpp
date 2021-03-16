#ifndef ast_unary_hpp
#define ast_unary_hpp

class Unary : public Expression 
{
    private:
        ExpressionPtr thing;
    protected:
        Unary(ExpressionPtr _thing) :
            thing(_thing)
        { }

        virtual const std::string getunary() const =0;

        virtual void print(std::ostream &dst) const override{
            dst << getunary();
            thing->print(dst);
        }
};

class IncrementUnary : public Unary
{
    public:
        IncrementUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }

        virtual const std::string getunary() const override{ 
        return "++"; 
    }
};

class DecrementUnary : public Unary
{
    public:
        DecrementUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "--"; 
    }
};

class NegUnary : public Unary
{
    public:
        NegUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "-"; 
    }
};

class NotUnary : public Unary
{
    public:
        NotUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "!"; 
    }
};

class AddrUnary : public Unary
{
    public:
        AddrUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "&"; 
    }
};

class SizeOfUnary : public Unary
{
    public:
        SizeOfUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "sizeof("; 
    }
};

class PointerUnary : public Unary
{
    public:
        PointerUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "*"; 
    }
};

class PositiveUnary : public Unary
{
    public:
        PositiveUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "+"; 
    }
};

class ComplementUnary : public Unary
{
    public:
        ComplementUnary(ExpressionPtr _thing) :
            Unary(_thing)
        { }
        virtual const std::string getunary() const override{ 
        return "~"; 
    }
};

#endif
