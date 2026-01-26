#ifndef MATHOPERATE_H
#define MATHOPERATE_H

#include <vector>

class Scalar {
private:
    double value;
    
public:
    Scalar(double val = 0);
    double getValue();
    void setValue(double val);
    Scalar power(double exp);
    Scalar root(double degree);
};

class Vector {
private:
    std::vector<double> data;
    
public:
    Vector(int size = 0);
    void resize(int size);
    void input();
    void print();
    std::vector<double> getData();  
    double get(int index);  
    void set(int index, double value);
    Vector multiplyElementwise(Vector& other);
    Vector multiplyWithMatrix(std::vector<std::vector<double>>& matrix);
};

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows, cols;
    
public:
    Matrix(int r = 0, int c = 0);
    void resize(int r, int c);
    void input();
    void print();
    std::vector<std::vector<double>> getData();
    Matrix multiply(Matrix& other);
    Vector multiplyWithVector(Vector& vec);
};

void MultiplicationVecAndMatrix();
void MultiplicationMatrix();
void VectorMultiply();
void exponentiation();
void square();

#endif
