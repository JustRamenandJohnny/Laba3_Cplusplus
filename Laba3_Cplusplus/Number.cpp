#include "Info.hpp"

Number::Number(int val) : value(val), stringValue(intToString(val)) {
    std::cout << " !!! " << "Constr: " << " | N: " << val << " S: " << stringValue << std::endl;
}

std::string Number::intToString(int val) const {
    static const std::map<int, std::string> numberMap = {
        {0, "����"}, {1, "����"}, {2, "���"}, {3, "���"}, {4, "������"},
        {5, "����"}, {6, "�����"}, {7, "����"}, {8, "������"}, {9, "������"},
        {10, "������"}, {11, "�����������"}, {12, "����������"}, {13, "����������"},
        {14, "������������"}, {15, "����������"}, {16, "�����������"},
        {17, "����������"}, {18, "������������"}, {19, "������������"},
        {20, "��������"}, //etclol
    };

    if (numberMap.find(val) != numberMap.end()) {
        return numberMap.at(val);
    }
    else {
        return std::to_string(val); //�������� ���� �� �� ������, ������� ���� ������, �� ����� ���� �� ����������� ����� � ������
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
