#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <cmath>
#include <memory>
#include <utility>

class Expression
{
    public:
        virtual void print(std::ostream &dst) =0;
};
#endif