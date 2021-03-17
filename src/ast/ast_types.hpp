#ifndef ast_types_hpp
#define ast_types_hpp

class String : public Expression{
    private:
        std::string* id;
    public:
        String(std::string* _id)
        : id(_id)
    {}

    const std::string getid() const{
        return *id; 
    }

    virtual void print(std::ostream &dst) const override{
        dst<<id;
    }
    
    virtual void codegen(std::ostream &dst) override{
        std::string label = newlabel();
        dst << ".data" << std::endl;
        dst << label << ".asciiz " <<  getid() << std::endl;

        dst << ".text" << std::endl;
        dst << "la " << "$t0, " << label << std::endl;
        dst << "sw " << "$t0, " << "($sp)" << std::endl;
        dst << "subu " << "$sp, " << "$sp, " << 4 << std::endl;
    }
};

class Double : public Expression{
    private:
        std::string* value;
    public:
        Double(std::string* _value) : 
        value(_value)
        {  }

    const std::string getid() const{
        return *value; 
    }

    virtual void print(std::ostream &dst) const override
    {
        dst<< *value;
    }
};

class Int : public Expression{
    private:
        std::string* value;
    public:
        Int(std::string* _value) : 
        value(_value)
        {  }

    const std::string getid() const{
        return *value; 
    }

    virtual void print(std::ostream &dst) const override
    {
        dst<< *value;
    }

    virtual void codegen(std::ostream &dst) override{
        dst << "li " << "$t0, " << getid() << std::endl; // load value into t0
        dst << "sw " << "$t0, " << "($sp)" << std::endl; // push onto stack
        dst << "subu " << "$sp, " << "$sp, " << 4; // decrement $sp
    }
};

#endif