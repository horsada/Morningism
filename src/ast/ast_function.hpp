#ifndef ast_function_hpp
#define ast_function_hpp

class Function : public Expression{
    private:
        std::string dec_spec;
        ExpressionPtr decl = NULL;
        ExpressionPtr statements = NULL;
        std::string return_type;
        std::string f_name;
    public:
        Function(std::string* _dec_spec, ExpressionPtr _mid, ExpressionPtr _right) :
        dec_spec(*_dec_spec),
        decl(_mid),
        statements(_right)
        { delete _dec_spec;}

        virtual ~Function(){
            delete decl;
            delete statements;
        }

        virtual void print(std::ostream &dst) override{
            dst << "Class Function: ";
            dst << " ";
            decl->print(dst);
            dst << " ";
            statements->print(dst);
        }

        void preamble(Table &head, std::ostream &dst, std::string f_name){
            dst << "\t.text\n" << "\t_" << f_name << ":" << std::endl;
        }

        void end(Table &head, std::ostream &dst, std::string f_name){
            int param_size = head.get_total_offset()*-1;
            dst << "\taddiu\t$sp\t$sp\t" << param_size << "\n" << "\tjr\t$ra\n\top" << std::endl;
        }

        void codegen(Table &head, std::ostream &dst){
            dst << "Class Function:" << std::endl;
            if(decl){
                decl->codegen(head,dst);
            }
            preamble(head, dst,f_name);
            if(statements){
                statements->codegen(head, dst);
            }
            end(head, dst, f_name);
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif