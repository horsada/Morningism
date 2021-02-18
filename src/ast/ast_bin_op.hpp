class BinOp : public Expression
{
    private:
        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;
        std::shared_ptr<std::string> op;
    public:
        BinOp(std::shared_ptr<Expression> _left, std::shared_ptr<std::string> _op, std::shared_ptr<Expression> _right) : 
            left(std::move(_left));
            op(std::move(_op));
            right(std::move(_right));
        { }
};