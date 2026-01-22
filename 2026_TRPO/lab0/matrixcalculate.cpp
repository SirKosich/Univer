#include "matrixcalculate.h"
#include <QString>

std::vector<std::vector<int>> MatrixCalculator::multiply(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B)
{
    int n = A.size();
    int k = A[0].size();
    int m = B[0].size();

    std::vector<std::vector<int>> C(n, std::vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int l = 0; l < k; l++) {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    return C;
}

bool MatrixCalculator::canMultiply(int colsA, int rowsB)
{
    return colsA == rowsB;
}

QString MatrixCalculator::matrixToString(const std::vector<std::vector<int>>& matrix)
{
    QString result;
    for (const auto& row : matrix) {
        for (int val : row) {
            result += QString::number(val) + " ";
        }
        result += "\n";
    }
    return result;
}

std::vector<std::vector<int>> MatrixCalculator::createMatrix(int rows, int cols, int defaultValue)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols, defaultValue));
}
