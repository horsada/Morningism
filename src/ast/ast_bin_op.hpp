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
    public:
        virtual const std::string getOpcode() const =0;

        virtual std::string getmips() =0;

        virtual void print(std::ostream &dst) override{
            dst << "Class BinOp:";
            dst <<"( ";
            left->print(dst);
            dst << " ";
            dst << getOpcode();
            dst << " ";
            right->print(dst);
            dst << " )";
        }

        virtual void codegen(std::ostream &dst) override{
            left->codegen(dst);
            right->codegen(dst);

            // genpop(); TODO: FIX - need to pop values in T0 and T1.
            // genpop());

            dst << getmips() << ", " << "$t0, " << "$t0, " << "$t1" << std::endl;

            // genpush("$t0");
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class AddOp : public BinOp
{
    public:
        AddOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "+"; 
    }
        virtual std::string getmips() override{
            return "add";
        }

};


class SubOp : public BinOp
{
    public:
        SubOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "-"; 
        }
        virtual std::string getmips() override{
            return "sub";
        }
};

class MulOp : public BinOp
{
    public:
        MulOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "*"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class DivOp : public BinOp
{
    public:
        DivOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "/"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class EqualToOp : public BinOp
{
    public:
        EqualToOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "=="; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class NotEqualToOp : public BinOp
{
    public:
        NotEqualToOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "!="; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class LessThanOp : public BinOp
{
    public:
        LessThanOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "<"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class GreaterThanOp : public BinOp
{
    public:
        GreaterThanOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return ">"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class OrOp : public BinOp
{
    public:
        OrOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "||"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class LeftShiftOp : public BinOp
{
    public:
        LeftShiftOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "<<"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class RightShiftOp : public BinOp
{
    public:
        RightShiftOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return ">>"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class GreaterThanOrEqualToOp : public BinOp
{
    public:
        GreaterThanOrEqualToOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return ">="; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class BitExcOrOp : public BinOp
{
    public:
        BitExcOrOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "^"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class BitIncOrOp : public BinOp
{
    public:
        BitIncOrOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "|"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class AndOp : public BinOp
{
    public:
        AndOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "&&"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class BitAndOp : public BinOp
{
    public:
        BitAndOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "&"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};

class ModuloOp : public BinOp
{
    public:
        ModuloOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "%"; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};  

class LessThanOrEqualToOp : public BinOp
{
    public:
        LessThanOrEqualToOp(ExpressionPtr _left, ExpressionPtr _right)
        : BinOp(_left, _right)
        {}
        virtual const std::string getOpcode() const override{ 
        return "<="; 
        }
        virtual std::string getmips() override{
            return "add";
        }
};  

#endif