#ifndef ast_function_hpp
#define ast_function_hpp

class Function : public Expression{
    private:
        ExpressionPtr dec_spec;
        ExpressionPtr mid;
        ExpressionPtr right;
        std::string return_type;
        std::string f_name;
    public:
        Function(ExpressionPtr _dec_spec, ExpressionPtr _mid, ExpressionPtr _right) :
        dec_spec(_dec_spec),
        mid(_mid),
        right(_right)
        { }

        virtual void print(std::ostream &dst) const override{
            dst << dec_spec;
            dst << " ";
            mid->print(dst);
            dst << " ";
            right->print(dst);
        }

        void preamble(std::ostream &dst, std::string f_name){
            dst << ".text\n" << "_" << f_name << ":" << std::endl;
        }

        void end(std::ostream &dst, std::string f_name){
            int param_size = 8;
            dst << "lw $ra, " << param_size << "($fp)" << std::endl;
            dst << "move $t0, $fp" << std::endl;
            dst << "lw $fp, " << param_size+4 << "($fp)" << std::endl;
            dst << "jr $ra" << std::endl; 
        }

        void codegen(std::ostream &dst){
            std::string f_name = "main";
            preamble(dst,f_name);
            right->codegen(dst);
            end(dst, f_name);
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif