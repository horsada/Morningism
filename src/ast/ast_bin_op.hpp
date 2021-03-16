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

        virtual void print(std::ostream &dst) const override{
            dst <<"( ";
            left->print(dst);
            dst << " ";
            dst << getOpcode();
            dst << " ";
            right->print(dst);
            dst << " )";
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
};  

#endif