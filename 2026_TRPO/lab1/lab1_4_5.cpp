#include <iostream>
#include <cmath>

void exponentiation(){
    
    double a, b, c;
    
    std::cout << "Введите сначала число, а потом степень, в которую её надо возвести" << std::endl;
    std::cin >> a >> b;
    
    c = pow(a,b);
    
    std::cout << a << " в степени " << b << " = " << c << std::endl;
}

void square(){
    double a, b;
    
    std::cout << "Введите число, а затем степень корня" << std::endl;
    std::cin >> a >> b;
    
    std::cout << "Корень " << b << " степени из числа " << a << " = " << pow(a, (1/b)) << std::endl;    
}

int main(){
    exponentiation();
    square();
    
    return 0;
}
