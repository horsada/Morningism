#ifndef table_hpp
#define table_hpp

class Table;

typedef std::shared_ptr<Table> TablePtr;

class Table{

    private:
    TablePtr prev;
    std::map<Expression, std::string> entries;
    std::map<std::string, TablePtr> func;

    public:
    Table(TablePtr _prev) :
    prev(_prev)
    { }

    std::string getentry(Expression entry){
        assert(entries.find(entry) != entries.end());
        return entries[entry];
    }

    bool checkentry(Expression entry){
        if(entries.find(entry) != entries.end()){
            return 1;
        }
        else{
            return 0;
        }
    }
};

#endif