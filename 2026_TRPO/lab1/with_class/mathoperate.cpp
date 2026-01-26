#include "mathoperate.h"
#include <iostream>
#include <cmath>

// Scalar
Scalar::Scalar(double val) : value(val) {}

double Scalar::getValue() {
    return value;
}

void Scalar::setValue(double val) {
    value = val;
}

Scalar Scalar::power(double exp) {
    return Scalar(pow(value, exp));
}

Scalar Scalar::root(double degree) {
    return Scalar(pow(value, 1.0 / degree));
}

// Vector
Vector::Vector(int size) {
    data.resize(size, 0);
}

void Vector::resize(int size) {
    data.resize(size, 0);
}

void Vector::input() {
    for (int i = 0; i < data.size(); i++) {
        std::cout << "Введите элемент " << i + 1 << ": ";
        std::cin >> data[i];
    }
}

void Vector::print() {
    for (double val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

std::vector<double> Vector::getData() {
    return data;
}

double Vector::get(int index) {
    if (index >= 0 && index < data.size()) {
        return data[index];
    }
    return 0;
}

void Vector::set(int index, double value) {
    if (index >= 0 && index < data.size()) {
        data[index] = value;
    }
}

Vector Vector::multiplyElementwise(Vector& other) {
    Vector result(data.size());
    for (int i = 0; i < data.size(); i++) {
        result.set(i, data[i] * other.get(i));
    }
    return result;
}

Vector Vector::multiplyWithMatrix(std::vector<std::vector<double>>& matrix) {
    int k = data.size();
    int n = matrix[0].size();
    Vector result(n);
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            result.set(j, result.get(j) + data[i] * matrix[i][j]);
        }
    }
    return result;
}

// Matrix
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(r, std::vector<double>(c, 0));
}

void Matrix::resize(int r, int c) {
    rows = r;
    cols = c;
    data.resize(r, std::vector<double>(c, 0));
}

void Matrix::input() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> data[i][j];
        }
    }
}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<double>> Matrix::getData() {
    return data;
}

Matrix Matrix::multiply(Matrix& other) {
    Matrix result(rows, other.cols);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            double sum = 0;
            for (int l = 0; l < cols; l++) {
                sum += data[i][l] * other.data[l][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

Vector Matrix::multiplyWithVector(Vector& vec) {
    Vector result(cols);
    
    // Умножение
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double current = result.get(j);
            result.set(j, current + vec.get(i) * data[i][j]);
        }
    }
    return result;
}
