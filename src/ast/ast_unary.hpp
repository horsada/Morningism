#ifndef ast_unary_hpp
#define ast_unary_hpp

class Unary : public Expression 
{
    private:
        ExpressionPtr thing;
        std::string* type_name;
    protected:
        Unary(ExpressionPtr _thing) :
            thing(_thing)
        { }

        Unary(std::string* _type_name) :
            type_name(_type_name),
            thing(NULL)
            {}

        virtual const std::string getunary() const =0;

        virtual void print(std::ostream &dst) override{
            dst << getunary();
            thing->print(dst);
        }

        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
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
        SizeOfUnary(std::string* _type_name) :
            Unary(_type_name)
        { }

        SizeOfUnary(ExpressionPtr _unary_expr) :
            Unary(_unary_expr)
        {}

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
