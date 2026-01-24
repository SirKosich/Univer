#include <iostream>
#include <vector>

std::vector<int> VectorMultiply(){
    int k, n;
    
    std::cout << "Введите количество элементов вектора 1 и 2" << std::endl;
	std::cin >> k;
    
    std::vector<int>A(k);
    std::vector<int>B(k);
    std::vector<int>C(k,0);
    
    for (int l = 0; l < k; l++){
        C[l] += A[l] * B[l];
    }
    
    return C;
}
