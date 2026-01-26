#include <iostream>
#include <windows.h>
#include "mathoperate.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

void setupUtf(){
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	#endif
}

int main(){
	setupUtf();
	
	int check = 1;
	do{
		std::cout << "Выберите вариант того, что хотели бы выполнить:" << std::endl;
		std::cout << "[1] Умножение вектора на матрицу" << std::endl;
		std::cout << "[2] Матричное произведение" << std::endl;
		std::cout << "[3] Скалярно произведение" << std::endl;
		std::cout << "[4] Возведение в степень" << std::endl;
		std::cout << "[5] Корень нужной вам степени" << std::endl;
		std::cout << "[0] Выйти из программы" << std::endl;
		std::cin >> check;
		
		switch (check){
			case 0:
				check = 0;
				break;
			case 1:
				MultiplicationVecAndMatrix();
				break;
			case 2:
				MultiplicationMatrix();
				break;
			case 3:
				VectorMultiply();
				break;
			case 4:
				exponentiation();
				break;
			case 5:
				square();
				break;
			default:
				std::cout << "Научитесь читать, пожалуйста" << std::endl;
		}
			
	} while (check != 0);
		
	return 0;
}
