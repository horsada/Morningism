#ifndef table_hpp
#define table_hpp

class Table;

class Table : public Expression{

    private:
    ExpressionPtr left;
    ExpressionPtr right;
    std::map<std::string, std::string> entries;
    std::map<std::string, ExpressionPtr> func;

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


/*
    std::string getentry(Expression entry){
        assert(entries.find(entry) != entries.end());
        std::string instr = entries[entry];
        return instr;
    }

    bool checkentry(Expression entry){
        if(entries.find(entry) != entries.end()){
            return 1;
        }
        else{
            return 0;
        }
    }

    void addentry(Expression entry, std::string operation){
        assert(entries.find(entry) == entries.end());
        entries[entry] = operation;
    }*/
};

#endif