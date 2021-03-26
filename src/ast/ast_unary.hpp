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

        virtual std::string getmips() =0;

        virtual void print(std::ostream &dst) override{
            dst << getunary();
            thing->print(dst);
        }

        virtual void codegen(Table &head, std::ostream &dst) override{
            if(dynamic_cast<Variable*>(thing)){
                dst << "\taddiu\t$sp\t$sp\t" << -4 << std::endl;
                head.add_total_offset(-4);

                std::string var = thing->getvar();
                int offset = head.get_stack_offset(var); //Find offset associated with left_var
                int diff = offset - head.get_total_offset(); 
                std::string destreg = head.getreg(thing->getvar());
                dst << "\tlw\t" << destreg << "\t" << diff << "($sp)" << std::endl;
                if(getmips() == "inc"){
                    dst << "\taddiu\t" << destreg << "\t" << destreg << "\t1" << std::endl;
                }
                else if(getmips() == "dec"){
                    dst << "\taddiu\t" << destreg << "\t" << destreg << "\t-1" << std::endl;
                }
                else if(getmips() == "neg"){
                    dst << "\tsubu\t" << destreg << "\t$0\t" << destreg << std::endl;
                }
                if(getmips() == "not"){
                    std::string end = head.newlabel();
                    std::string gtz = head.newlabel();
                    dst << "\tbne\t" << destreg << "\t$0\t" << gtz << "\n"
                    << "\tnop\n" 
                    << "\taddiu\t" << destreg << "\t$0\t1\n"
                    << "\tb\t" << end << "\n"
                    << "\tnop\n"
                    << gtz << "\taddu\t" << destreg << "\t$0\t$0\n"
                    << end << std::endl;
                }
                else if(getmips() == "comp"){
                    dst << "\tnot\t" << destreg << "\t$0\t" << destreg << std::endl;
                }
                else{
                    // do nothing
                }
                dst << "\tsw\t" << destreg << "\t0($sp)" << std::endl;
            }
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
        virtual std::string getmips() override{
            return "inc";
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

        virtual std::string getmips() override{
            return "dec";
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
        virtual std::string getmips() override{
            return "neg";
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
        virtual std::string getmips() override{
            return "not";
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
        virtual std::string getmips() override{
            return "addr";
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

    virtual std::string getmips() override{
            return "inc";
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
    virtual std::string getmips() override{
            return "inc";
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
    virtual std::string getmips() override{
            return "inc";
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

        virtual std::string getmips() override{
            return "comp";
        }
};

#endif
