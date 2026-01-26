#include <iostream>
#include "mathoperate.h"

void MultiplicationMatrix() {
    int n, k, m;
    std::cout << "Введите размеры матриц (n k m): ";
    std::cin >> n >> k >> m;
    
    Matrix A(n, k);
    Matrix B(k, m);
    
    std::cout << "Матрица A:" << std::endl;
    A.input();
    
    std::cout << "Матрица B:" << std::endl;
    B.input();
    
    Matrix C = A.multiply(B);
    
    std::cout << "Результат:" << std::endl;
    C.print();
}
