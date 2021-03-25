#ifndef ast_types_hpp
#define ast_types_hpp

class String : public Expression{
    private:
        std::string id;
    public:
        String(std::string* _id)
        : id(*_id)
    {delete _id;}

    const std::string getid() const{
        return id; 
    }

    virtual void print(std::ostream &dst) override{
        dst<<id;
    }
    
    virtual void codegen(Table &head, std::ostream &dst) override{
        std::string label = "label";
        dst << ".data" << std::endl;
        dst << label << ".asciiz " <<  getid() << std::endl;

        dst << ".text" << std::endl;
        dst << "la " << "$t0, " << label << std::endl;
        dst << "sw " << "$t0, " << "($sp)" << std::endl;
        dst << "subu " << "$sp, " << "$sp, " << 4 << std::endl;
    }
    virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class Double : public Expression{
    private:
        //std::string value;
        double value;
    public:
    /*
        Double(std::string* _value) : 
        value(*_value)
        { delete _value;}

    const std::string getid() const{
        return value; 
    }
    */
    Double(double _value) : 
        value(_value)
        { }
    virtual void print(std::ostream &dst) override
    {
        dst << value;
    }
    virtual void codegen(Table &head, std::ostream &dst) override{
            dst << "Class Double: Unimplemented feature" << std::endl;
        }
        virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class IntConst : public Expression{
    private:
        //std::string value;
        int32_t value;
    public:
    /*
        IntConst(std::string* _value) : 
        value(*_value)
        { delete _value; }

    const std::string getid() const{
        return value; 
    }
    */

   IntConst(int32_t _value) : 
        value(_value)
        { }
    virtual void print(std::ostream &dst) override
    {   
        dst << "Class IntConst:";
        dst<< value;
    }

    virtual int32_t getint() override{
        return value;
    }

    virtual void codegen(std::ostream &dst) override{
        dst << "Class IntConst:" << std::endl;
        dst << "\tli\t" << /* destreg */ "$t0\t" << value << std::endl; // load value into destreg
    }

    virtual void codegen(Table &head, std::ostream &dst) override{
        dst << "Class IntConst:" << std::endl;
    }

    virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

class FloatConst : public Expression{
    private:
        //std::string value;
        double value;
    public:
        /*FloatConst(std::string* _value) : 
        value(*_value)
        { delete _value; }
        */
        FloatConst(double _value) : 
        value(_value)
        { }
    /*
    const std::string getid() const{
        return value; 
    }
    */
    virtual void print(std::ostream &dst) override
    {
        dst <<"Class FloatConst:";
        dst<< value;
    }

    virtual double getfloat() override{
        return value;
    }

    virtual void codegen(Table &head, std::ostream &dst) override{
        /*dst << "li " << "$t0, " << value << std::endl; // load value into t0
        dst << "sw " << "$t0, " << "($sp)" << std::endl; // push onto stack
        dst << "subu " << "$sp, " << "$sp, " << 4; // decrement $sp*/
        dst << "Class FloatConst:" << std::endl;
    }
    virtual void pushexpr(ExpressionPtr _expr) override{
            std::cout << "Unimplemented feature" << std::endl;
        }
};

#endif