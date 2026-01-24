#include <iostream>
#include <vector>

std::vector<std::vector<int>> MultiplicationMatrix(){
 int k,n,m;
 std::cin >> n >> k >> m;
 
 std::vector<std::vector<int>>A(n, std::vector<int>(k));
 std::vector<std::vector<int>>B(k, std::vector<int>(m));
 std::vector<std::vector<int>>C(n, std::vector<int>(m, 0));
 
 for (int i = 0; i < n; i++){
  for (int j = 0; j < k; j++){
	std::cout << "Введите " << j + 1 << " элемент " << i + 1 << " строки матрицы A: ";
    std::cin >> A[i][j];
   }
 }
 
 for (int i = 0; i < n; i++){
  for (int j = 0; j < k; j++){
	std::cout << "Введите " << j + 1 << " элемент " << i + 1 << " строки матрицы B: ";
	std::cin >> B[i][j];
   }
 }
 
/* for (int i = 0; i < n; i++){
  for (int j = 0; j < m; j++){
    for (int l = 0; l < k; l++){
      C[i][j] += A[i][l] * B[l][j];
     }
    std::cout << C[i][j] << " "; 
   }
  std::cout << "\n";
 } */
 
 return C;
}

