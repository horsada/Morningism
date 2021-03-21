#ifndef table_hpp
#define table_hpp

class Table;
class Scope;

typedef Table* TablePtr;

class Table{

    private:
    std::stack<int> table_stack;
    std::map<std::string, int> offset; // offset < 0 for local variables, offset > 0 for global variables
    std::map<std::string, std::string> regs; // for storing register values, (Variable, Register)
    std::map<std::string, std::string> labels; // To avoid storing same string literal value more than once

    public:
    Table() {}

    void genPush(std::string val){
        table_stack.push(std::stoi(val));
    }

    void genPop(){
        table_stack.pop();
    }

    std::string newsreg(){
        static int count = 0;
        std::string dest = "$s" + std::to_string(count);
        count++;
        return dest;
    }

    std::string newtreg(){
        static int count = 0;
        std::string dest = "$t" + std::to_string(count);
        count++;
        return dest;
    }

    void startmips(std::ostream &dst){
        dst << "\t.data" << std::endl;
        dst << "_newline_:" << std::endl;
        dst << "\t.asciiz n" << std::endl;
        dst << "\ttext" << std::endl;
        dst << ".global main" << std::endl;
    }
};

#endif