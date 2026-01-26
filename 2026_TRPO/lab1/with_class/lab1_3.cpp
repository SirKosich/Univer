#include <iostream>
#include "mathoperate.h"

void VectorMultiply() {
    int k;
    std::cout << "Введите размер векторов: ";
    std::cin >> k;
    
    Vector A(k);
    Vector B(k);
    
    std::cout << "Вектор A:" << std::endl;
    A.input();
    
    std::cout << "Вектор B:" << std::endl;
    B.input();
    
    Vector C = A.multiplyElementwise(B);
    
    std::cout << "Результат: ";
    C.print();
}
