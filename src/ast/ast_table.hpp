#ifndef table_hpp
#define table_hpp

class Table;

typedef std::shared_ptr<Table> TablePtr;

class Table{

    private:
    TablePtr prev;
    std::map<std::string, std::string> entries;
    std::map<std::string, TablePtr> func;

    public:
    Table(TablePtr _prev) :
    prev(_prev)
    { }
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