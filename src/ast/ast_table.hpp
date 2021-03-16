#ifndef table_hpp
#define table_hpp

class Table;

class Table : public Expression{

    private:
    std::map<std::string, std::string> entries;
    std::map<std::string, ExpressionPtr> func;

    public:
    Table();

    Table(ExpressionPtr _expr){

    }

    Table(ExpressionPtr _left, ExpressionPtr _right){
        
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