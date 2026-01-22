#ifndef MATRIXCALCULATE_H
#define MATRIXCALCULATE_H

#include <vector>
#include <QString>

class MatrixCalculator
{
public:
    // Умножение матриц
    static std::vector<std::vector<int>> multiply(
        const std::vector<std::vector<int>>& A,
        const std::vector<std::vector<int>>& B);

    // Проверка возможности умножения
    static bool canMultiply(int colsA, int rowsB);

    // Преобразование матрицы в строку
    static QString matrixToString(const std::vector<std::vector<int>>& matrix);

    // Создание пустой матрицы
    static std::vector<std::vector<int>> createMatrix(int rows, int cols, int defaultValue = 0);
};

#endif // MATRIXCALCULATE_H
