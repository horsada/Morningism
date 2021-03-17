#ifndef table_hpp
#define table_hpp

class Table : public Expression{

    private:
    ExpressionPtr left;
    ExpressionPtr right;
    std::stack<int> table_stack;
    std::map<std::string, int> offset; // offset < 0 for local variables, offset > 0 for global variables
    std::map<std::string, std::string> labels; // To avoid storing same string literal value more than once

    public:
    Table();

    Table(ExpressionPtr _expr){
        left = _expr;
    }

    Table(ExpressionPtr _left, ExpressionPtr _right){
        left = _left;
        right = _right;
    }

    virtual void print(std::ostream &dst) const override{
        if(right == NULL){
            left->print(dst);
        }
        else{
            left->print(dst);
            dst << " ";
            right->print(dst);
        }
    }

    void genPush(std::string val){
        table_stack.push(std::stoi(val));
    }

    void genPop(){
        table_stack.pop();
    }
};

#endif