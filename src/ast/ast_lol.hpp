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
        
};

class Return : public Expression
{
    private:
        ExpressionPtr right;
    public:
        Return(ExpressionPtr _right) : 
            right(_right)
        {}       
};

class GoTo : public Expression
{
    private:
        std::string* label;
    public:
        GoTo(std::string* _label) : 
            label(_label)
        {}       
};


class Continue : public Expression
{
    private:
        std::string* label;
    public:
        Continue(){

        }
};


class Break : public Expression
{
    private:
        std::string* label;
    public:
        Break(){
            
        }
};

#endif