#ifndef types_hpp
#define types_hpp

class Char : public Expression{
    private:
        std::string id;
    public:
        Char(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const{
        return id; 
    }

    virtual void print(std::ostream &dst) const override
    {
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

    const double getId() const{
        return value; 
    }

    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
};

#endif