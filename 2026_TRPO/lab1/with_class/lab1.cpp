#include <iostream>
#include <vector>
#include "mathoperate.h"

void MultiplicationVecAndMatrix(){
    int k, n;
    std::cout << "Введите количество элементов вектора (эта величина также отвечает за кол-во строк в матрице), также введите кол-во столбцов в матрице" << std::endl;
    std::cin >> k >> n;
    
    Vector A(k);
    Matrix B(k, n);
    
    std::cout << "Ввод вектора A:" << std::endl;
    A.input();
    
    std::cout << "Ввод матрицы B:" << std::endl;
    B.input();
    
    Vector C = B.multiplyWithVector(A);
    
    std::cout << "Результат умножения вектора на матрицу: ";
    C.print();
}
