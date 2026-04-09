#include <iostream>
#include <vector>


/**
 * Función para multiplicar dos matrices cuadradas de tamaño n x n.
 * El método "Naive" o tradicional utiliza tres bucles (O(n^3)).
 * 1. El primer bucle (i) recorre las filas de la primera matriz.
 * 2. El segundo bucle (j) recorre las columnas de la segunda matriz.
 * 3. El tercer bucle (k) realiza la suma de los productos (producto punto).
 */
std::vector<std::vector<int>> multiplyNaive(const std::vector<std::vector<int>>& M1, const std::vector<std::vector<int>>& M2, int dimensionMatriz) {
    
    // Matriz de salida de tamaño n x n iniciada en 0
    std::vector<std::vector<int>> resultado(dimensionMatriz, std::vector<int>(dimensionMatriz, 0));

    for (int i = 0; i < dimensionMatriz; i++) {
        for (int j = 0; j < dimensionMatriz; j++) {
            for (int k = 0; k < dimensionMatriz; k++) {
                // La posición [i][j] es la suma de M1[i][k] * M2[k][j]
                resultado[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    return resultado;
}