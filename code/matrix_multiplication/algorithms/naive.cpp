#include <iostream>
#include <vector>


/**
 * Función para multiplicar dos matrices cuadradas de tamaño n x n.
 * El método "Naive" o tradicional utiliza tres bucles (O(n^3)).
 * * Paso 1: El primer bucle (i) recorre las filas de la primera matriz.
 * Paso 2: El segundo bucle (j) recorre las columnas de la segunda matriz.
 * Paso 3: El tercer bucle (k) realiza la suma de los productos (producto punto).
 */
std::vector<std::vector<int>> multiplyNaive(const std::vector<std::vector<int>>& M1, const std::vector<std::vector<int>>& M2, int n) {
    
    // Matriz de salida de tamaño n x n inicializada en 0
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                // La posición [i][j] es la suma de M1[i][k] * M2[k][j]
                result[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    return result;
}
