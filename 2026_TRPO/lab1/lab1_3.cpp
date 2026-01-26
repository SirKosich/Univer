#include <iostream>
#include <vector>
#include "mathoperate.h"

void VectorMultiply(){
    int k, n;
    
    std::cout << "Введите количество элементов вектора 1 и 2" << std::endl;
	std::cin >> k;
    
    std::vector<int>A(k);
    std::vector<int>B(k);
    std::vector<int>C(k,0);
    
    for (int i = 0; i < k; i++){
		std::cout << "Введите " << i + 1 << " элемент вектора A: ";
		std::cin >> A[i];
	}
	
	for (int i = 0; i < k; i++){
		std::cout << "Введите " << i + 1 << " элемент вектора B: ";
		std::cin >> B[i];
	}
    
    for (int l = 0; l < k; l++){
        C[l] += A[l] * B[l];
    }

}
