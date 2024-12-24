

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <numeric> // Для accumulate
#include "Info.hpp"


void processVector(const std::vector<Number>& numbers) {
    std::cout << "\n" << std::endl;
    std::cout << "--------processVector-" << std::endl;
    for (const auto& num : numbers) {
        std::cout << "Number: " << num.getValue() << ", String: " << num.getStringValue() << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    std::cout << "\n" << std::endl;
}

void processList(const std::list<Number>& numbers) {
    std::cout << "\n" << std::endl;
    std::cout << "--------processList-" << std::endl;
    for (const auto& num : numbers) {
        std::cout << "Number: " << num.getValue() << ", String: " << num.getStringValue() << std::endl;
    }
    std::cout << "----------------------" << std::endl;


}

Number createNumber(int val) {//just for fun
    return Number(val);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // 1. Создать вектор v1 размером от 500 до 1000 элементов с случайными объектами класса Number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_size(500, 1000);
    std::uniform_int_distribution<> dist_value(1, 1000);

    size_t v1_size = dist_size(gen);
    std::vector<Number> v1;
    v1.reserve(v1_size);

    for (size_t i = 0; i < v1_size; ++i) {
        v1.emplace_back(dist_value(gen));
    }

    // 2. Создать вектор v2, поместив в него последние 200 элементов вектора v1
    size_t b = v1.size() > 200 ? v1.size() - 200 : 0;
    std::vector<Number> v2(v1.begin() + b, v1.end());

    // Удаляем элементы из v1
    v1.erase(v1.begin() + b, v1.end());

    // 3. Сформировать список list1 из первых n (20-50) наибольших элементов v1, отсортированных
    std::uniform_int_distribution<> dist_n1(20, 50);
    size_t n1 = dist_n1(gen);

    std::partial_sort(v1.begin(), v1.begin() + n1, v1.end(), [](const Number& a, const Number& b) {
        return a.getValue() > b.getValue();
        });

    std::list<Number> list1(v1.begin(), v1.begin() + n1);
    v1.erase(v1.begin(), v1.begin() + n1);

    // 4. Сформировать список list2 из последних n (20-50) наименьших элементов v2
    size_t n2 = dist_n1(gen); // Для удобства используем тот же диапазон

    std::partial_sort(v2.begin(), v2.begin() + n2, v2.end(), [](const Number& a, const Number& b) {
        return a.getValue() < b.getValue();
        });

    std::list<Number> list2(v2.begin(), v2.begin() + n2);
    v2.erase(v2.begin(), v2.begin() + n2);

    // 5. Найти элемент со средним значением в list1 и перегруппировать элементы
    int sum = 0;
    for (const auto& num : list1) {
        sum += num.getValue();
    }
    int avg = sum / static_cast<int>(list1.size());

    list1.sort([](const Number& a, const Number& b) { return a.getValue() > b.getValue(); });
    auto it = std::partition(list1.begin(), list1.end(), [avg](const Number& num) {
        return num.getValue() > avg;
        });

    // 6. Удалить из list2 все нечётные элементы
    list2.remove_if([](const Number& num) {
        return num.getValue() % 2 != 0;
        });

    // 7. Создать вектор v3 из элементов, присутствующих в v1 и v2
    std::vector<Number> v3;
    std::sort(v1.begin(), v1.end(), [](const Number& a, const Number& b) {
        return a.getValue() < b.getValue();
        });
    std::sort(v2.begin(), v2.end(), [](const Number& a, const Number& b) {
        return a.getValue() < b.getValue();
        });

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3), [](const Number& a, const Number& b) {
        return a.getValue() < b.getValue();
        });

    // 8. Привести list1 и list2 к одинаковому размеру
    while (list1.size() > list2.size()) {
        list1.pop_front();
    }
    while (list2.size() > list1.size()) {
        list2.pop_front();
    }

    // Сформировать list3 из пар элементов list1 и list2
    std::list<std::pair<Number, Number>> list3;
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    while (it1 != list1.end() && it2 != list2.end()) {
        list3.emplace_back(*it1, *it2);
        ++it1;
        ++it2;
    }

    // 9. Создать пары для v1 и v2 без предварительного приведения к одинаковому размеру
    std::vector<std::pair<Number, Number>> pairs;
    size_t min_size = std::min(v1.size(), v2.size());

    for (size_t i = 0; i < min_size; ++i) {
        pairs.emplace_back(v1[i], v2[i]);
    }

    return 0;
}
//int main() {
//
//    setlocale(LC_ALL, "Russian");
//
//    Number num1(1);
//    Number num2(2);
//    Number num3(3);
//    Number num4(4);
//
//    Number* num5 = new Number(5);
//    Number* num6 = new Number(6);
//    Number* num7 = new Number(7);
//    Number* num8 = new Number(8);
//
//    std::cout << "--------start-" << std::endl;
//
//    std::list<Number> numberList;
//    numberList.push_back(num1);
//    std::cout << "--------push_back-" << std::endl;
//    numberList.push_back(num2);
//    std::cout << "--------push_back-" << std::endl;
//
//    std::vector<Number> numberVector;
//
//    numberVector.emplace_back(num3);
//    std::cout << "--------emplace_back-" << std::endl;
//    numberVector.emplace_back(num4);
//    std::cout << "--------emplace_back-" << std::endl;
//
//    numberVector.emplace_back(*num5);
//    std::cout << "--------emplace_back-" << std::endl;
//    numberVector.emplace_back(*num6);
//    std::cout << "--------emplace_back-" << std::endl;
//    numberVector.emplace_back(*num7);
//    std::cout << "--------emplace_back-" << std::endl;
//    numberVector.emplace_back(*num8);
//    std::cout << "--------emplace_back-" << std::endl;
//
//    std::cout << "\n" << std::endl;
//    std::cout << "vv - assign - vv" << std::endl;
//    std::cout << "\n" << std::endl;
//
//
//
//    //!noexcept
//    Number num9 = createNumber(9);
//    std::cout << "[ Created number9: " << num9.getValue() << ", String: " << num9.getStringValue() << " ]" << std::endl;
//
//    std::cout << "Modifying number (!noexcept): " << num1.getValue() << std::endl;
//    num1 = num9;
//
//    std::cout << " to " << num9.getValue() << std::endl;
//
//    std::cout << "\n" << std::endl;
//
//    //noexcept
//    Number num0 = createNumber(0);
//    std::cout << "[ Created number0: " << num0.getValue() << ", String: " << num0.getStringValue() << " ]" << std::endl;
//
//    std::cout << "Modifying number (noexcept): " << num2.getValue() << std::endl;
//    num2 = std::move(num0);
//
//    std::cout << " to " << num0.getValue() << std::endl;
//
//    std::cout << "\n" << std::endl;
//
//    //++ --
//    Number sum = num1 + num2;
//    Number difference = num4 - num3;
//
//    std::cout << "Сумма: " << sum.getValue() << ", Строка: " << sum.getStringValue() << std::endl;
//    std::cout << "Разность: " << difference.getValue() << ", Строка: " << difference.getStringValue() << std::endl;
//
//
//    processList(numberList);
//    processVector(numberVector);
//
//    delete num5, num6, num7, num8;
//
//    return 0;
//}
