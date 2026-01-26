#include <iostream>
#include "mathoperate.h"

void exponentiation() {
    double a, b;
    std::cout << "Введите число и степень: ";
    std::cin >> a >> b;
    
    Scalar num(a);
    Scalar result = num.power(b);
    
    std::cout << a << "^" << b << " = " << result.getValue() << std::endl;
}

void square() {
    double a, b;
    std::cout << "Введите число и степень корня: ";
    std::cin >> a >> b;
    
    Scalar num(a);
    Scalar result = num.root(b);
    
    std::cout << "Корень " << b << " степени из " << a << " = " << result.getValue() << std::endl;
}
