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
            dst << "Class BinOp:" << std::endl;
            if(dynamic_cast<Variable*>(left)){
                std::string left_var = left->getvar();
                // std::string left_reg = head.getreg(left_var); Find register associated with left_var
                if(dynamic_cast<Variable*>(right)){
                    std::string right_var = right->getvar();
                    // std::string right_reg = head.getreg(right_var); Find register associated with right_var
                    dst << "\t" << getmips() << "\t$destReg"<< "\t" << "$left_reg, " << "$right_reg" << std::endl;
                }
                else if (dynamic_cast<IntConst*>(right)){
                    right->codegen(dst);
                    // std::string right_reg = head.getreg(right_var); Find register associated with right_var
                    dst << "\t" << getmips() << "\t$destReg" << "\t" << "$left_reg, " << "$right_reg" << std::endl;
                }
                else{
                    dst << "Unimplemented binop" << std::endl;
                }
            }
            else if(dynamic_cast<IntConst*>(left)){
               left->codegen(dst); // this codegen should store the value in a register
                if(dynamic_cast<Variable*>(right)){
                    std::string right_var = right->getvar();
                    // std::string right_reg = head.getreg(right_var); Find register associated with right_var
                    dst << "\t" << getmips() << "\t$destReg"<< "\t" << "$left_reg, " << "$right_reg" << std::endl;
                }
                else if (dynamic_cast<IntConst*>(right)){
                    right->codegen(dst);
                    dst << "\t" << getmips() << "\t$destReg"<< "\t" << "$left_reg, " << "$right_reg" << std::endl;
                }
                else{
                    dst << "Unimplemented binop" << std::endl;
                }
            }
            else{
                dst << "Unimplemented Binop" << std::endl;
            }
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