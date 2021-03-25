#ifndef table_hpp
#define table_hpp

class Scope;
class Table;

typedef Table* TablePtr;

class Table{

    private:
    std::string func_name;
    std::stack<int> table_stack;
    int total_offset;
    std::map<std::string, int> stack_offset; // offset < 0 for local variables, offset > 0 for global variables
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

    int get_total_offset(){
        return total_offset;
    }

    void add_total_offset(int offset){
        total_offset += offset;
    }

    std::string newsreg(){
        static int count = 0;
        if(count < 8){
            std::string dest = "$s" + std::to_string(count); //s0 always used as default mem start
            count++;
            return dest;
        }
        else{
            count = 0;
            std::string dest = "$s" + std::to_string(count); //s0 always used as default mem start
            count++;
            return dest;
        }
    }

        std::string newareg(){
        static int count = 0;
        if(count < 5){
            std::string dest = "$a" + std::to_string(count); //s0 always used as default mem start
            count++;
            return dest;
        }
        else{
            count = 0;
            std::string dest = "$a" + std::to_string(count); //s0 always used as default mem start
            count++;
            return dest;
        }
    }

    std::string newtreg(){
        static int count = 0;
        if(count < 8){
            std::string dest = "$t" + std::to_string(count); //s0 always used as default mem start
            count++;
            return dest;
        }
        else{
            count = 0;
            std::string dest = "$t" + std::to_string(count); //s0 always used as default mem start
            count++;
            return dest;
        }
    }

    void insert_reg(std::string val, std::string reg){
        regs.insert(std::make_pair(val, reg));
        assert(regs.find(val) != regs.end());
    }

    void insert_stack_offset(std::string val, int offset){
        stack_offset.insert(std::make_pair(val,offset));
    }

    std::string newlabel(){
    static int count = 0;
    std::string dest = "label" + std::to_string(count) + ":";
    count++;
    return dest;
    }

    std::string getreg(std::string val){
        return regs[val];
    }

    int regs_size(){
        return regs.size();
    }

    void startmips(std::ostream &dst){
        dst << "\t.data" << std::endl;
        dst << "_newline_:" << std::endl;
        dst << "\t.asciiz n" << std::endl;
        dst << "\ttext" << std::endl;
        dst << ".global main" << std::endl;
    }

    int get_stack_offset(std::string var){
        return stack_offset[var];
    }

    void putfunction(std::string name){
        func_name = name;
    }

    std::string get_func_name(){
            return func_name;
        }

};

#endif