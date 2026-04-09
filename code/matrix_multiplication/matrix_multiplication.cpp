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

// Declaraciones selectivas para que el codigo se vea mas limpio
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;
using std::getline;
using std::to_string;

typedef vector<vector<int>> Matrix;

// Prototipos
// el prototipo es slo la representacion de la funcion pero no se incluye como tal
Matrix multiplyNaive(const Matrix& M1, const Matrix& M2, int n);
Matrix strassen(const Matrix& A, const Matrix& B, int n);

/**
 * Lee la memoria máxima (VmPeak) que ha usado el proceso actual de la ejecucion en KB.
 * El VmPeak es el pico de memoria que se alcanza en el proeso
 * https://docs.kernel.org/filesystems/proc.html traspasar al latex
 */
long obtenerMemoriaPeak() {
    ifstream statusFile("/proc/self/status");
    string line;
    while (getline(statusFile, line)) {
        if (line.find("VmPeak:") != string::npos) {
            // Extrae el número de la línea "VmPeak"
            return std::stol(line.substr(line.find_first_of("0123456789")));
        }
    }
    return 0; 
}

Matrix leerMatriz(string filename, int n) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir: " << filename << endl;
        exit(1);
    }
    Matrix mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> mat[i][j];
        }
    }
    return mat;
}

/**
 * Guarda tiempo y memoria.
 * code/matrix_multiplication/data/measurements/
 */
void guardarMetricas(string algoritmo, int n, double time, long memory) {
    string path = "data/measurements/" + algoritmo + "_" + to_string(n) + "_metricas.txt";
    ofstream outFile(path, std::ios::app);
    if (outFile.is_open()) {
        // Se gaurda Tiempo(s) Memoria(KB)
        outFile << time << " " << memory << "\n";
        outFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 8) {
        cerr << "Uso: ./matrix_test <n> <algoritmo> <tipo> <dominio> <muestra> <matriz1> <matriz2>\n";
        return 1;
    }

    // n es la dimencion de las matrices. 16(2^4), 32(2^5), 64(2^6), 128(2^7), 256(2^8), 512(2^9), 1024(2^10)
    int dimensionMatriz = std::stoi(argv[1]);
    string algoritmo = argv[2];
    string tipo = argv[3];
    string dominio = argv[4];
    string muestra = argv[5];
    string f1 = argv[6];
    string f2 = argv[7];

    Matrix Matriz1 = leerMatriz(f1, dimensionMatriz);
    Matrix Matriz2 = leerMatriz(f2, dimensionMatriz);
    Matrix result;

    // --- MEDICION DE TIEMPO CON CHRONO ---
    auto start = std::chrono::high_resolution_clock::now();

    if (algoritmo == "naive") {
        result = multiplyNaive(Matriz1, Matriz2, dimensionMatriz);
    } else if (algoritmo == "strassen") {
        result = strassen(Matriz1, Matriz2, dimensionMatriz);
    } else {
        cerr << "Algoritmo no reconocido: " << algoritmo << "\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoTotal = end - start;

    // --- MEDICIÓN DE MEMORIA CON VmPeak ---
    long memoriaUsada = obtenerMemoriaPeak();

    // Guardar en data/measurements/
    guardarMetricas(algoritmo, dimensionMatriz, tiempoTotal.count(), memoriaUsada);

    // --- GUARDAR MATRIZ RESULTANTE ---
    // el resultado se guarda en data/matrix_output/ con el formato n_algoritmo_out.txt
    string outPath = "data/matrix_output/" + to_string(dimensionMatriz) + "_" + tipo + "_" + dominio + "_" + muestra + "_out.txt";
    ofstream outResult(outPath);
    // Recorremos cada fila de la matriz
    for (int i = 0; i < dimensionMatriz; i++) {
        for (int j = 0; j < dimensionMatriz; j++) {
            outResult << result[i][j];
            if (j == dimensionMatriz - 1) {
                outResult << ""; 
            } else {
                outResult << " ";
            }
        }
        outResult << "\n";
    }

    return 0;
}