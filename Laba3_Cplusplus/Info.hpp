
#include <iostream>
#include <string>
#include <map>

class Number {
private:

    int value;
    std::string stringValue;

    std::string intToString(int val) const;

public:
    Number(int val);//Number(int val, const std::string& val1);


    Number(const Number& other);//Constr copy
    Number& operator=(const Number& other);//Oper = copy


    Number(Number&& other) noexcept;//Constr move 
    Number& operator=(Number&& other) noexcept;//Oper = move


    Number operator+(const Number& other) const; // +
    Number operator-(const Number& other) const; // -



    ~Number();//dеструктор


    std::string getStringValue() const;
    int getValue() const;
};

