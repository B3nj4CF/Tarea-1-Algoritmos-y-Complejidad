#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Función de Partición:
 * El objetivo es elegir un "pivote" y reordenar el arreglo de modo que:
 * 1. Los elementos menores al pivote queden a la izquierda.
 * 2. Los elementos mayores al pivote queden a la derecha.
 */
int partition(std::vector<int>& arr, int low, int high) {
    // Elegimos el último elemento como pivote
    int pivot = arr[high]; 
    
    // Índice del elemento más pequeño. Indica la posición correcta
    // hasta ahora del pivote final.
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot) {
            i++; // Incrementamos el índice del elemento más pequeño
            std::swap(arr[i], arr[j]); // Intercambiamos
        }
    }
    // Colocamos el pivote en su posición correcta
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/**
 * Función principal de Quick Sort:
 * Utiliza la técnica de "Dividir y Conquistar" de forma recursiva.
 */
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi es el índice de partición, arr[pi] ya está en su lugar
        int pi = partition(arr, low, high);

        // Ordenamos los elementos por separado antes y después de la partición
        quickSort(arr, low, pi - 1);  // Mitad izquierda
        quickSort(arr, pi + 1, high); // Mitad derecha
    }
}
