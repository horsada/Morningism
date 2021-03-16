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
};

class Double : public Expression{
    private:
        double value;
    public:
        Double(double _value) : 
        value(_value)
        {  }

    const double getid() const{
        return value; 
    }

    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
};

#endif