#include "Info.hpp"

Number::Number(int val) : value(val), stringValue(intToString(val)) {
    std::cout << " !!! " << "Constr: " << " | N: " << val << " S: " << stringValue << std::endl;
}

std::string Number::intToString(int val) const {
    static const std::map<int, std::string> numberMap = {
        {0, "ноль"}, {1, "один"}, {2, "два"}, {3, "три"}, {4, "четыре"},
        {5, "пять"}, {6, "шесть"}, {7, "семь"}, {8, "восемь"}, {9, "девять"},
        {10, "десять"}, {11, "одиннадцать"}, {12, "двенадцать"}, {13, "тринадцать"},
        {14, "четырнадцать"}, {15, "пятнадцать"}, {16, "шестнадцать"},
        {17, "семнадцать"}, {18, "восемнадцать"}, {19, "девятнадцать"},
        {20, "двадцать"}, //etclol
    };

    if (numberMap.find(val) != numberMap.end()) {
        return numberMap.at(val);
    }
    else {
        return std::to_string(val); //всецифры мира же не запишу, поэтому если выйдет, то пусть хотя бы преобразует число в строку
    }
}

Number::Number(const Number& other) {
    value = other.value;
    stringValue = other.stringValue;

    std::cout << " /c/ " << "Copy constr: " << std::to_string(other.value) << std::endl;
}

Number::Number(Number&& other) noexcept {
    value = other.value;
    stringValue = std::move(other.stringValue);

    std::cout << " >c> " << "Move constr: " << std::to_string(other.value) << std::endl;
}

Number& Number::operator=(const Number& other) {
    if (this != &other) {
        value = other.value;
        stringValue = other.stringValue;
    }
    std::cout << " /a/ " << "Copy assign: " << std::to_string(other.value) << std::endl;
    return *this;
}

Number& Number::operator=(Number&& other) noexcept {
    if (this != &other) {
        value = other.value;
        stringValue = std::move(other.stringValue);
    }
    std::cout << " >a> " << "Move assign: " << std::to_string(other.value) << std::endl;
    return *this;
}

Number Number::operator+(const Number& other) const {
    return Number(value + other.value);
}

Number Number::operator-(const Number& other) const {
    return Number(value - other.value);
}

Number::~Number() {
    std::cout << " [ - Destructor - ] " << std::endl;
}

std::string Number::getStringValue() const {
    return stringValue;
}

int Number::getValue() const {
    return value;
}
