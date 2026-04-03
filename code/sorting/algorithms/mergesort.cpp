#include <iostream>
#include <vector>

/**
 * Función que mezcla dos sub-arreglos ordenados en uno solo.
 * Paso 1: Crear arreglos temporales para la izquierda y derecha.
 * Paso 2: Comparar elementos y copiarlos en orden al arreglo original.
 */
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Vectores temporales
    std::vector<int> L(n1), R(n2);

    // Copiar datos a los vectores temporales
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Índices iniciales para los sub-arreglos y el mezclado
    int i = 0, j = 0, k = left;

    // Se comparan los elementos de L y R y se inserta el menor
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si quedan
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si quedan
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Función principal de Merge Sort (recursiva).
 * Divide el arreglo en mitades hasta que el tamaño sea 1, luego mezcla.
 */
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Se calcula el punto medio para evitar desbordamiento en números grandes
        int mid = left + (right - left) / 2;

        // Recursión: Dividir la mitad izquierda
        mergeSort(arr, left, mid);
        // Recursión: Dividir la mitad derecha
        mergeSort(arr, mid + 1, right);

        // Combinar las mitades ordenadas
        merge(arr, left, mid, right);
    }
}
