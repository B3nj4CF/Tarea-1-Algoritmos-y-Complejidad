#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>

// Aquí debes incluir o declarar las funciones de tus otros archivos
// según como estructures tu Makefile.
void mergeSort(std::vector<int>& arr, int left, int right);
void quickSort(std::vector<int>& arr, int low, int high);

/**
 * Función para leer el arreglo desde los archivos generados por el script de Python.
 * El formato del nombre es {n}_{t}_{d}_{m} según el anexo A.1.
 */
std::vector<int> readArray(std::string filename) {
    std::ifstream file(filename);
    int val;
    std::vector<int> arr;
    while (file >> val) {
        arr.push_back(val);
    }
    return arr;
}

/**
 * Función para guardar el tiempo de ejecución en la carpeta de mediciones.
 */
void saveMeasurement(std::string algorithm, std::string testCase, double duration) {
    std::ofstream outFile("measurements/sorting/" + algorithm + "_" + testCase + ".txt", std::ios::app);
    outFile << duration << "\n";
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: ./sorting <algoritmo> <archivo_entrada>\n";
        return 1;
    }

    std::string algo = argv[1];
    std::string fileName = argv[2];
    
    // 1. Leer los datos [cite: 99]
    std::vector<int> data = readArray(fileName);
    int n = data.size();

    // 2. Tomar tiempo de inicio
    auto start = std::chrono::high_resolution_clock::now();

    // 3. Ejecutar el algoritmo seleccionado [cite: 46]
    if (algo == "merge") {
        mergeSort(data, 0, n - 1);
    } else if (algo == "quick") {
        quickSort(data, 0, n - 1);
    } else if (algo == "std_sort") {
        std::sort(data.begin(), data.end());
    }

    // 4. Tomar tiempo de fin
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    // 5. Guardar la medición para el informe 
    saveMeasurement(algo, fileName, diff.count());

    // 6. Escribir el resultado ordenado en el archivo de salida [cite: 105]
    std::ofstream outResult(fileName + "_out.txt");
    for (int x : data) outResult << x << " ";
    
    return 0;
}