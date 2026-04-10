/**
 * TAREA 1 - INF-221 ALGORITMOS Y COMPLEJIDAD
 * Estudiante: Benjamin Campos
 * Algoritmo de Strassen (Implementación pura osea que tiene naive)
 */

#include <vector>

using std::vector;
typedef vector<vector<int>> Matrix;

// Función auxiliar para sumar matrices
Matrix sumar(const Matrix& A, const Matrix& B, int dimensionMatriz) {
    Matrix res(dimensionMatriz, vector<int>(dimensionMatriz));
    for (int i = 0; i < dimensionMatriz; i++)
        for (int j = 0; j < dimensionMatriz; j++)
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

// Función auxiliar para restar matrices
Matrix restar(const Matrix& A, const Matrix& B, int dimensionMatriz) {
    Matrix res(dimensionMatriz, vector<int>(dimensionMatriz));
    for (int i = 0; i < dimensionMatriz; i++)
        for (int j = 0; j < dimensionMatriz; j++)
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

Matrix strassen(const Matrix& A, const Matrix& B, int dimensionMatriz) {
    // caso base importante para evitar recursión infinita
    if (dimensionMatriz == 1) {
        Matrix res(1, vector<int>(1));
        res[0][0] = A[0][0] * B[0][0];
        return res;
    }

    int newSize = dimensionMatriz / 2;
    Matrix a11(newSize, vector<int>(newSize)), a12(newSize, vector<int>(newSize)),
           a21(newSize, vector<int>(newSize)), a22(newSize, vector<int>(newSize)),
           b11(newSize, vector<int>(newSize)), b12(newSize, vector<int>(newSize)),
           b21(newSize, vector<int>(newSize)), b22(newSize, vector<int>(newSize));

    // Dividir las matrices en 4 submatrices
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

    // Las 7 multiplicaciones de Strassen
    Matrix p1 = strassen(sumar(a11, a22, newSize), sumar(b11, b22, newSize), newSize);
    Matrix p2 = strassen(sumar(a21, a22, newSize), b11, newSize);
    Matrix p3 = strassen(a11, restar(b12, b22, newSize), newSize);
    Matrix p4 = strassen(a22, restar(b21, b11, newSize), newSize);
    Matrix p5 = strassen(sumar(a11, a12, newSize), b22, newSize);
    Matrix p6 = strassen(restar(a21, a11, newSize), sumar(b11, b12, newSize), newSize);
    Matrix p7 = strassen(restar(a12, a22, newSize), sumar(b21, b22, newSize), newSize);

    // Combinar resultados para la matriz C
    Matrix c11 = sumar(restar(sumar(p1, p4, newSize), p5, newSize), p7, newSize);
    Matrix c12 = sumar(p3, p5, newSize);
    Matrix c21 = sumar(p2, p4, newSize);
    Matrix c22 = sumar(restar(sumar(p1, p3, newSize), p2, newSize), p6, newSize);

    // Unificar en una sola matriz de n x n
    Matrix res(dimensionMatriz, vector<int>(dimensionMatriz));
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