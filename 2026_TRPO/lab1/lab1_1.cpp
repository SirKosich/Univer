#include <iostream>
#include <vector>

std::vector<int> VectorCalculate(){
	int k, n;
	std::cout << "Введите количество элементов вектора (эта величина также отвечает за кол-во строк в матрице), также введите кол-во столбцов в матрице" << std::endl;
	std::cin >> k >> n;
	
	std::vector<int>A(k);
	std::vector<std::vector<int>>B(k, std::vector<int>(n));
	std::vector<int>C(n, 0);
	
	for (int i = 0; i < k; i++){
		std::cout << "Введите " << i + 1 << " элемент вектора: ";
		std::cin >> A[i];
	}
	
	for (int i = 0; i < k; i++){
		for (int j = 0; j < n; j++){
			std::cout << "Введите " << j + 1 << " элемент " << i + 1 << " строки матрицы: ";
			std::cin >> B[i][j];
		}
	}
	
	for (int i = 0; i < k; i++){
		for (int j = 0; j < n; j++){
			C[j] += A[i] * B[i][j];
		}
	}
	
	for (int i = 0; i < n; i++){
		std::cout << C[i] << " ";
	}
	
	return С;
}


