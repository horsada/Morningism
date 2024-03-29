#ifndef ast_loop_hpp
#define ast_loop_hpp

class For : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        For(ExpressionPtr _left, ExpressionPtr _right, ExpressionPtr iterator, ExpressionPtr statement) : 
            left(_left),
            right(_right)
        {}
        virtual void print(std::ostream &dst) override{
            dst << "Class For:";
            left->print(dst);
            right->print(dst);
        }

        virtual void codegen(std::ostream &dst) override{
            dst << "Unimplemented feature" << std::endl;
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class While : public Expression
{
    private:
        ExpressionPtr left;
        ExpressionPtr right;
    public:
        While(ExpressionPtr _left, ExpressionPtr _right) : 
            left(_left),
            right(_right)
        {} 
        virtual void print(std::ostream &dst) override{
            dst << "Class While:";
            left->print(dst);
            right->print(dst);
        }
        virtual void codegen(Table &head, std::ostream &dst) override{
            //dst << "Class While:" << std::endl;
            std::string begin = head.newlabel();
            std::string end = head.newlabel();
            assert(left != NULL);
            dst << begin << std::endl;
            int begin_offset = head.get_total_offset();
            left->codegen(head, dst);
            if(dynamic_cast<BinOp*>(left)){
                std::string dest_reg = left->getdestreg();
                dst << "\tbeq\t" << dest_reg << "\t$0\t" << end << "\n" << "\tnop\n";
            }
            if(right){
                right->codegen(head,dst);
            }
            int after_offset = head.get_total_offset();
            int diff = abs(begin_offset - after_offset);
            dst << "\taddiu\t$sp\t$sp\t" << diff << std::endl;
            dst << "\tb\t" << begin <<"\n" << "\tnop\n" << end << ":\n";
        } 
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif