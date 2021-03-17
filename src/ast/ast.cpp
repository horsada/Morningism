#include "ast.hpp"

std::string newSreg(){
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

std::string newlabel(){
    static int count = 0;
    std::string dest = "label" + std::to_string(count) + ":";
    count++;
    return dest;
}
/* TODO: FIX
void genpop(std::string t){
    head.genPop(t);
}
*/