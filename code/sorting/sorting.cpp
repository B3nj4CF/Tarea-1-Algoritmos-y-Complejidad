#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
#include <sys/resource.h> // Para medir memoria en Arch Linux

// Prototipos
void mergeSort(std::vector<int>& arr, int left, int right);
void quickSort(std::vector<int>& arr, int low, int high);

/**
 * Lee el arreglo. No necesita el tamaño N al inicio porque usamos push_back,
 * lo cual es más flexible para los archivos que genera tu script.
 */
std::vector<int> leerArray(std::string filename) {
    std::ifstream file(filename);
    int valor;
    std::vector<int> array;
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return array;
    }
    while (file >> valor) {
        array.push_back(valor);
    }
    return array;
}

/**
 * Guarda el tiempo y la memoria (VmPeak). 
 * Usamos el tamaño N para organizar el archivo y que sea fácil de graficar.
 */
void guardarMedicion(std::string algoritmo, int n, double duracion) {
    // Esto crea un archivo por algoritmo y tamaño, ej: measurements/sorting/quicksort_1000.txt
    std::string path = "data/measurements/" + algoritmo + "_" + std::to_string(n) + "_metricas.txt";
    std::ofstream outFile(path, std::ios::app);
    
    // Medimos el pico de memoria consumido por el proceso (VmPeak)
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    long memory = usage.ru_maxrss;

    if (outFile.is_open()) {
        outFile << duracion << " " << memory << "\n";
        outFile.close();
    }
}

int main(int argc, char* argv[]) {
    // Cambiamos a 3 argumentos obligatorios: algoritmo, tamaño y ruta
    if (argc < 4) {
        std::cerr << "Uso: ./sorting_test <n> <algoritmo> <archivo_entrada>\n";
        return 1;
    }

    int n_size = std::stoi(argv[1]);
    std::string algoritmo = argv[2];
    std::string ruta_archivo = argv[3];
    
    // 1. Cargar datos
    std::vector<int> data = leerArray(ruta_archivo);
    if (data.empty()) return 1;

    // 2. Medir tiempo
    auto start = std::chrono::high_resolution_clock::now();

    if (algoritmo == "mergesort") {
        mergeSort(data, 0, data.size() - 1);
    } else if (algoritmo == "quicksort") {
        quickSort(data, 0, data.size() - 1);
    } else if (algoritmo == "sort_stl") {
        std::sort(data.begin(), data.end());
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    // 3. Guardar métricas (Tiempo y Memoria)
    guardarMedicion(algoritmo, n_size, diff.count());

    // 4. Opcional: Guardar resultado ordenado (solo para verificar)
    // std::ofstream outResult(ruta_archivo + "_out.txt");
    // for (int x : data) outResult << x << " ";

    std::cout << "Finalizado: " << algoritmo << " para N=" << n_size << " en " << diff.count() << "s" << std::endl;
    
    return 0;
}