/**
 * TAREA 1 - INF-221 ALGORITMOS Y COMPLEJIDAD
 * Estudiante: Benjamin Campos
 * Universidad Tecnica Federico Santa Maria
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
#include <sys/resource.h> 

// Declaraciones selectivas para que el codifo se vea mas lumpio
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::cout;
using std::endl;
using std::to_string;

// Prototipos de las funciones
void mergeSort(vector<int>& arr, int left, int right);
void quickSort(vector<int>& arr, int low, int high);


/**
 * Lee el arreglo desde el archivo.
 */
vector<int> leerArray(string filename) {
    ifstream file(filename);
    int valor;
    vector<int> array;
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << endl;
        return array;
    }
    
    while (file >> valor) {
        array.push_back(valor);
    }
    
    file.close();
    return array;
}

/**
 * Guarda el tiempo y el pico de memoria RAM física en KB.
 */
void guardarMedicion(string algoritmo, int n, double duracion) {
    string path = "data/measurements/" + algoritmo + "_" + to_string(n) + "_metricas.txt";
    ofstream outFile(path, std::ios::app);
    
    // Medición de memoria getrusage
    // https://man7.org/linux/man-pages/man2/getrusage.2.html peragr en el reporte
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    long memoriaUsada = usage.ru_maxrss;

    if (outFile.is_open()) {
        outFile << duracion << " " << memoriaUsada << "\n";
        outFile.close();
    }
}

void guardarArrayOrdenado(const vector<int>& arr, string rutaEntrada) {
    size_t lastSlash = rutaEntrada.find_last_of("/");
    string nombre = (lastSlash == string::npos) ? rutaEntrada : rutaEntrada.substr(lastSlash + 1);

    nombre.replace(nombre.find(".txt"), 4, "_out.txt");

    ofstream outFile("data/array_output/" + nombre);
    for (int x : arr) {
        outFile << x << "\n";
    }
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: ./sorting_test <dimension> <algoritmo> <archivo_entrada>" << endl;
        return 1;
    }

    int tamanoDimension = std::stoi(argv[1]);
    string algoritmo = argv[2];
    string ruta_archivo = argv[3];
    
    // 1. Cargar datos
    vector<int> data = leerArray(ruta_archivo);
    if (data.empty() && tamanoDimension > 0) return 1;

    // 2. Medir tiempo
    auto start = std::chrono::high_resolution_clock::now();

    if (algoritmo == "mergesort") {
        mergeSort(data, 0, (int)data.size() - 1);
    } else if (algoritmo == "quicksort") {
        quickSort(data, 0, (int)data.size() - 1);
    } else if (algoritmo == "sort") {
        std::sort(data.begin(), data.end());
    } else {
        cerr << "Algoritmo no reconocido: " << algoritmo << endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    // 3. Guardar métricas
    guardarMedicion(algoritmo, tamanoDimension, diff.count());

    cout << "Finalizado: " << algoritmo << " para N=" << tamanoDimension << " en " << diff.count() << "s" << endl;
    guardarArrayOrdenado(data, ruta_archivo);
    return 0;
}