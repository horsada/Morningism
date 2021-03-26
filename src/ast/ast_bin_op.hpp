#ifndef ast_bin_op_hpp
#define ast_bin_op_hpp

class BinOp : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
        std::string dest_reg = "Unassigned destreg";
        std::string type = "";
    protected:
        BinOp(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}
    public:
        virtual const std::string getOpcode() const =0;

        virtual std::string getmips() =0;

        virtual std::string getfmips(){
            std::cout << "Unimplemented getfmips";
        }

        virtual void put_type(std::string _type) override{
            type = _type;
        }

        virtual std::string get_type() override{
            return type;
        }

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

        virtual void codegen(Table &head, std::ostream &dst) override{
            //dst << "Class BinOp:" << std::endl;
            dest_reg = head.newsreg();
            std::string left_temp = "";
            std::string right_temp = "";
            if(dynamic_cast<Variable*>(left)){
                std::string left_var = left->getvar();
                if(head.getreg(left_var) != ""){
                    left_temp = head.getreg(left_var);
                }
                else{
                    left_temp = head.newtreg();
                }
                    int left_offset = head.get_stack_offset(left_var); //Find offset associated with left_var
                    int left_diff = left_offset - head.get_total_offset(); 

                    if(left_temp.find('f') != std::string::npos){
                        dest_reg = head.newfreg();
                        dst << "\tlwc1\t" << left_temp << "\t" << left_diff << "($sp)" << std::endl;
                        dst << "\t" << getfmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                    }
                    else{
                        dst << "\tlw\t" << left_temp << "\t" << left_diff << "($sp)" << std::endl;
                    }

                if(dynamic_cast<Variable*>(right)){
                    std::string right_var = right->getvar();
                    if(head.getreg(right_var) != ""){
                    right_temp = head.getreg(right_var);
                }
                else{
                    right_temp = head.newtreg();
                }
                    int right_offset = head.get_stack_offset(right_var); //Find offset associated with left_var
                    int right_diff = right_offset - head.get_total_offset();
                    if(right_temp.find('f') != std::string::npos){
                        dest_reg = head.newfreg();
                        dst << "\tlwc1\t" << right_temp << "\t" << right_diff << "($sp)" << std::endl;
                        dst << "\t" << getfmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                    }
                    else{
                        dst << "\tlw\t" << right_temp << "\t" << right_diff << "($sp)" << std::endl;
                        dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                    }
                }
                else if (dynamic_cast<IntConst*>(right)){
                    std::string right_temp = head.newtreg();
                    dst << "\tli\t" << right_temp << "\t" << right->getint() << std::endl;
                    // std::string right_reg = head.getreg(right_var); Find register associated with right_var
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                }
                else{
                    dst << "Unimplemented binop" << std::endl;
                }
            }
            else if(dynamic_cast<IntConst*>(left)){
                std::string left_temp = head.newtreg();
                dst << "\tli\t" << left_temp << "\t" << left->getint() << std::endl;
                if(dynamic_cast<Variable*>(right)){
                    std::string right_var = right->getvar();
                    std::string right_temp = head.newtreg();
                    int right_offset = head.get_stack_offset(right_var); //Find offset associated with left_var
                    int right_diff = right_offset - head.get_total_offset();
                    dst << "\tlw\t" << right_temp << "\t" << right_diff << "($sp)" << std::endl;
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                }
                else if (dynamic_cast<IntConst*>(right)){
                    std::string right_temp = head.newtreg();
                    dst << "\tli\t" << right_temp << "\t" << right->getint() << std::endl;
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                }
                else if(dynamic_cast<BinOp*>(right)){
                    right->codegen(head, dst);
                    std::string right_destreg = right->getdestreg();
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_destreg << std::endl;
                }
                else{
                    dst << "Unimplemented binop" << std::endl;
                }
            }
            else{
                dst << "Unimplemented Binop" << std::endl;
            }
            //dst << "\tsw\t" << dest_reg << "\t" << "0($sp)" << std::endl;
            head.insert_stack_offset(dest_reg, head.get_total_offset());
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }

        virtual std::string getdestreg() override{
            return dest_reg;
        }

        virtual void codegen(Table &head, std::ostream &dst, std::string arg_reg) override{
            dst << "Class BinOp:" << std::endl;
            dest_reg = arg_reg;
            if(dynamic_cast<Variable*>(left)){
                std::string left_var = left->getvar();
                std::string left_temp = head.newtreg();
                int left_offset = head.get_stack_offset(left_var); //Find offset associated with left_var
                int left_diff = left_offset - head.get_total_offset(); 
                dst << "\tlw\t" << left_temp << "\t" << left_diff << "($sp)" << std::endl;
                if(dynamic_cast<Variable*>(right)){
                    std::string right_var = right->getvar();
                    std::string right_temp = head.newtreg();
                    int right_offset = head.get_stack_offset(right_var); //Find offset associated with left_var
                    int right_diff = right_offset - head.get_total_offset();
                    if(right_temp.find('f') != std::string::npos){
                        dest_reg = head.newfreg();
                        dst << "\tlwc1\t" << right_temp << "\t" << right_diff << "($sp)" << std::endl;
                        dst << "\t" << getfmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                    }
                    else{
                        dst << "\tlw\t" << right_temp << "\t" << right_diff << "($sp)" << std::endl;
                        dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                    }
                }
                else if (dynamic_cast<IntConst*>(right)){
                    std::string right_temp = head.newtreg();
                    dst << "\tli\t" << right_temp << "\t" << right->getint() << std::endl;
                    // std::string right_reg = head.getreg(right_var); Find register associated with right_var
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                }
                else{
                    dst << "Unimplemented binop" << std::endl;
                }
            }
            else if(dynamic_cast<IntConst*>(left)){
                std::string left_temp = head.newtreg();
                dst << "\tli\t" << left_temp << "\t" << left->getint() << std::endl;
                if(dynamic_cast<Variable*>(right)){
                    std::string right_var = right->getvar();
                    std::string right_temp = head.newtreg();
                    int right_offset = head.get_stack_offset(right_var); //Find offset associated with left_var
                    int right_diff = right_offset - head.get_total_offset();
                    dst << "\tlw\t" << right_temp << "\t" << right_diff << "($sp)" << std::endl;
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                }
                else if (dynamic_cast<IntConst*>(right)){
                    std::string right_temp = head.newtreg();
                    dst << "\tli\t" << right_temp << "\t" << right->getint() << std::endl;
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_temp << std::endl;
                }
                else if(dynamic_cast<BinOp*>(right)){
                    right->codegen(head, dst);
                    std::string right_destreg = right->getdestreg();
                    dst << "\t" << getmips() << "\t" << dest_reg << "\t" << left_temp << "\t" << right_destreg << std::endl;
                }
                else{
                    dst << "Unimplemented binop" << std::endl;
                }
            }
            else{
                dst << "Unimplemented Binop" << std::endl;
            }
            //dst << "\tsw\t" << dest_reg << "\t" << "0($sp)" << std::endl;
            head.insert_stack_offset(dest_reg, head.get_total_offset());
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

        virtual std::string getfmips() override{
            return "add.s";
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

        virtual std::string getfmips() override{
            return "sub.s";
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
            return "mul";
        }

        virtual std::string getfmips() override{
            return "mul.s";
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
            return "div";
        }

        virtual std::string getfmips() override{
            return "div.s";
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
            return "seq";
        }

        virtual std::string getfmips() override{
            return "c.eq.s";
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
            return "sne";
        }

        virtual std::string getfmips() override{
            return "c.ne.s";
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
            return "slt";
        }

        virtual std::string getfmips() override{
            return "c.lt.s";
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
            return "sgt";
        }

        virtual std::string getfmips() override{
            return "c.gt.s";
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
            return "or";
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
            return "sll";
        }
        virtual std::string getfmips() override{
            return "add.s";
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
            return "srl";
        }
        virtual std::string getfmips() override{
            return "add.s";
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
            return "sge";
        }

        virtual std::string getfmips() override{
            return "c.ge.s";
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
            return "xor";
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
            return "or";
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
            return "and";
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
            return "rem";
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
            return "sle";
        }

        virtual std::string getfmips() override{
            return "c.le.s";
        }
};  

#endif