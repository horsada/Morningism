#ifndef ast_lol_hpp
#define ast_lol_hpp

class Jump : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        Jump(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}
        
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class Return : public Expression
{
    private:
        ExpressionPtr right;
        std::string type = "";
    public:
        Return(ExpressionPtr _right) : 
            right(_right)
        {}       

        virtual void print(std::ostream &dst) override{
            dst << "Class Return:";
            right->print(dst);
        }
        virtual void codegen(Table &head, std::ostream &dst) override{
           // dst << "Class Return:" << std::endl;
            std::string destReg = "";
            right->codegen(head, dst);
            if(dynamic_cast<BinOp*>(right)){
                head.add_total_offset(-4);
                dst << "\taddiu\t$sp\t$sp\t" << -4 << std::endl;
                destReg = right->getdestreg();
                int offset = head.get_stack_offset(destReg); //Find offset associated with left_var
                int diff = offset - head.get_total_offset();
                if(destReg.find("f") != std::string::npos){
                    dst << "\tlwc1\t" << destReg << "\t" << diff << "($sp)" << std::endl;
                    dst << "\tmfc1\t$v0\t" << destReg << std::endl;
                }
                else{
                    dst << "\tsw\t" << destReg << "\t" << 0 << "($sp)" << std::endl;
                    dst << "\tlw\t$v0\t" << 0 << "($sp)" << std::endl;
                } 
            }
            else if(dynamic_cast<Variable*>(right)){
                //dst << "Class Variable in return" << std::endl;
                //destReg = head.getreg(right->getvar());
                int offset = head.get_stack_offset(right->getvar());
                int diff = offset-head.get_total_offset();
                std::string reg = head.getreg(right->getvar());
                if(reg.find("f") != std::string::npos){
                    std::string f_reg = head.newfreg();
                    dst << "\tlwc1\t" << f_reg << "\t" << diff << "($sp)" << std::endl;
                    dst << "\tmfc1\t$v0\t" << f_reg << std::endl;
                }
                else{
                    //dst << "Class Variable in return" << std::endl;
                    //destReg = head.getreg(right->getvar());
                    dst << "\tlw\t$v0\t" << diff << "($sp)" << std::endl;
                }
            }
            else if(dynamic_cast<IntConst*>(right)){
                std::string val = std::to_string(right->getint());
                dst << "\tli\t$v0" << "\t" << val << std::endl;
            }
            else if(dynamic_cast<FloatConst*>(right)){
                std::string f_reg = head.newfreg();
                double val = right->getfloat();
                dst << "\tli.s\t" << f_reg << "\t" << val << std::endl; 
                dst << "\tmtc1\t$v0\t" << f_reg << std::endl;
            }
            else{
                dst << "Return: Unimplemented feature";
            }
            if(destReg != ""){
                //dst << "\tlw\t$v0\t" << destReg << std::endl;
                //dst << "\tmove\t$v0,\t" << "destReg:" << destReg << std::endl;
            }
            else{
               // dst << "\tb\t\n" << "\tnop\n";
            }
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }

        virtual std::string get_type(){
            return type;
        }

        virtual void put_type(std::string _type) override{
            type = _type;
        }
};

class GoTo : public Expression
{
    private:
        std::string* label;
    public:
        GoTo(std::string* _label) : 
            label(_label)
        {}
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }      

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};


class Continue : public Expression
{
    private:
        std::string* label;
    public:
        Continue(){

        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }

        void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature" << std::endl;
        }
};


class Break : public Expression
{
    private:
        std::string* label;
    public:
        Break(){
            
        }
        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        } 

        void pushexpr(ExpressionPtr _expr){
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif