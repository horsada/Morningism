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
            dst << "\t.text\n" << "\t_" << f_name << ":" << std::endl;
        }

        void end(std::ostream &dst, std::string f_name){
            int param_size = 8;
            dst << "\tlw\t$ra,\t" << param_size << "($fp)" << std::endl;
            dst << "\tmove\t$t0,\t$fp" << std::endl;
            dst << "\tlw\t$fp,\t" << param_size+4 << "($fp)" << std::endl;
            dst << "\tjr\t$ra" << std::endl; 
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