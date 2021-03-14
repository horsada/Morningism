#ifndef ast_function_hpp
#define ast_function_hpp

class Function : public Expression{
    private:
        std::string dec_spec;
        ExpressionPtr mid;
        ExpressionPtr right;
    public:
        Function(std::string &_dec_spec, ExpressionPtr _mid, ExpressionPtr _right) :
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
};

#endif