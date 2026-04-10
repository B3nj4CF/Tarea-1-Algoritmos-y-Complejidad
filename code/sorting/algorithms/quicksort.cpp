#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

/**
 * Partición de hoare es mas eficiente que la de lomuto y asi no se demora para las pruebas
 * pasar al ingotme https://www.geeksforgeeks.org/dsa/hoares-vs-lomuto-partition-scheme-quicksort/
 */
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low + (high - low) / 2]; // Pivote al centro
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        
        if (i >= j) return j;
        
        swap(arr[i], arr[j]);
    }
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}