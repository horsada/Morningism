#ifndef ast_function_hpp
#define ast_function_hpp

class Function : public Expression{
    private:
        std::string* dec_spec;
        ExpressionPtr decl = NULL;
        ExpressionPtr statements = NULL;
        std::string return_type;
        std::string f_name;
    public:
        Function(std::string* _dec_spec, ExpressionPtr _mid, ExpressionPtr _right) :
        dec_spec(_dec_spec),
        decl(_mid),
        statements(_right)
        { }

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
            statements->codegen(dst);
            end(dst, f_name);
        }

        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif