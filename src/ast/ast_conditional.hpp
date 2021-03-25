#ifndef ast_if_hpp
#define ast_if_hpp

class If : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        If(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {}

        virtual void print(std::ostream &dst) override{
            dst << "Class If:";
            left->print(dst);
            right->print(dst);
        }
        virtual void codegen(Table &head, std::ostream &dst) override{
            std::string elselabel = "Else:" + head.newlabel();
            std::string endlabel = "EndIF:" + head.newlabel();
            if(dynamic_cast<BinOp*>(left)){
                left->codegen(head, dst);

                dst << "\tbeq\t" << left->getdestreg() << "\t$0\t" << elselabel << "\n" << "\tnop\n";
            }
            if(right){
                right->codegen(head,dst);
            }
            dst << "\tj\t" << endlabel << "\n" << "\tnop\n" << elselabel << ":\n";
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class IfElse : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr mid;
        ExpressionPtr right;
    public:
        IfElse(ExpressionPtr _left, ExpressionPtr _mid, ExpressionPtr _right) : 
            left(_left),
            mid(_mid),
            right(_right)
        {}
        virtual void print(std::ostream &dst) override{
            dst << "Class IfElse:";
            left->print(dst);
            right->print(dst);
        }
        virtual void codegen(Table &head, std::ostream &dst) override{
            std::string elselabel = "Else:" + head.newlabel();
            std::string endlabel = "EndIF:" + head.newlabel();
            if(left){
                left->codegen(head, dst);
            }
            dst << "\tbeq\t$" << left->getdestreg() << "\t$0\t" << elselabel << "\n" << "\tnop\n";
            if(mid){
                mid->codegen(head,dst);
            }
            dst << "\tj\t" << endlabel << "\n" << "\tnop\n" << elselabel << ":\n";
            if(right){
                right->codegen(head, dst);
                dst << endlabel << ":\n";
            }
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }

};

class Switch : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        Switch(ExpressionPtr _left, ExpressionPtr _right) : 
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

#endif