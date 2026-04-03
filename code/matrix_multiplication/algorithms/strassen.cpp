#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

// Funciones auxiliares para sumar y restar matrices
Matrix sumar(const Matrix& A, const Matrix& B, int n) {
    Matrix res(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

Matrix restar(const Matrix& A, const Matrix& B, int n) {
    Matrix res(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

/**
 * Algoritmo de Strassen
 * 1. Divide las matrices A y B en 4 submatrices de tamaño (n/2)x(n/2).
 * 2. Calcula 7 productos (P1 a P7) de forma recursiva.
 * 3. Combina los resultados para formar la matriz final.
 */
Matrix strassen(const Matrix& A, const Matrix& B, int n) {
    // Caso base: si la matriz es de 1x1, multiplicar directamente
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = n / 2;
    Matrix a11(newSize, std::vector<int>(newSize));
    Matrix a12(newSize, std::vector<int>(newSize));
    Matrix a21(newSize, std::vector<int>(newSize));
    Matrix a22(newSize, std::vector<int>(newSize));
    Matrix b11(newSize, std::vector<int>(newSize));
    Matrix b12(newSize, std::vector<int>(newSize));
    Matrix b21(newSize, std::vector<int>(newSize));
    Matrix b22(newSize, std::vector<int>(newSize));

    // Dividir matrices en 4 submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular los 7 productos de Strassen
    Matrix p1 = strassen(sumar(a11, a22, newSize), sumar(b11, b22, newSize), newSize);
    Matrix p2 = strassen(sumar(a21, a22, newSize), b11, newSize);
    Matrix p3 = strassen(a11, restar(b12, b22, newSize), newSize);
    Matrix p4 = strassen(a22, restar(b21, b11, newSize), newSize);
    Matrix p5 = strassen(sumar(a11, a12, newSize), b22, newSize);
    Matrix p6 = strassen(restar(a21, a11, newSize), sumar(b11, b12, newSize), newSize);
    Matrix p7 = strassen(restar(a12, a22, newSize), sumar(b21, b22, newSize), newSize);

    // Combinar para obtener C11, C12, C21, C22
    Matrix c11 = sumar(restar(sumar(p1, p4, newSize), p5, newSize), p7, newSize);
    Matrix c12 = sumar(p3, p5, newSize);
    Matrix c21 = sumar(p2, p4, newSize);
    Matrix c22 = sumar(restar(sumar(p1, p3, newSize), p2, newSize), p6, newSize);

    // Agrupar en la matriz resultante
    Matrix res(n, std::vector<int>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            res[i][j] = c11[i][j];
            res[i][j + newSize] = c12[i][j];
            res[i + newSize][j] = c21[i][j];
            res[i + newSize][j + newSize] = c22[i][j];
        }
    }
    return res;
}