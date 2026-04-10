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
#include <sys/resource.h>

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
Matrix multiplyNaive(const Matrix& M1, const Matrix& M2, int n);
Matrix strassen(const Matrix& A, const Matrix& B, int n);

/**
    Obtiene el pico de memoria RAM física (RSS) usada por el proceso.
 */
long obtenerMemoriaPeak() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss;
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

void guardarMetricas(string algoritmo, int n, double time, long memory) {
    string path = "data/measurements/" + algoritmo + "_" + to_string(n) + "_metricas.txt";
    ofstream outFile(path, std::ios::app);
    if (outFile.is_open()) {
        outFile << time << " " << memory << "\n";
        outFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 8) {
        cerr << "Uso: ./matrix_test <n> <algoritmo> <tipo> <dominio> <muestra> <matriz1> <matriz2>\n";
        return 1;
    }

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

    // --- MEDICION DE TIEMPO ---
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

    // --- MEDICIÓN DE MEMORIA CON RUSAGE ---
    // Esto captura el pico máximo de RAM física durante la ejecución
    long memoriaUsada = obtenerMemoriaPeak();

    guardarMetricas(algoritmo, dimensionMatriz, tiempoTotal.count(), memoriaUsada);

    // --- GUARDAR MATRIZ RESULTANTE ---
    string outPath = "data/matrix_output/" + to_string(dimensionMatriz) + "_" + tipo + "_" + dominio + "_" + muestra + "_out.txt";
    ofstream outResult(outPath);
    for (int i = 0; i < dimensionMatriz; i++) {
        for (int j = 0; j < dimensionMatriz; j++) {
            outResult << result[i][j];
            if (j < dimensionMatriz - 1) outResult << " ";
        }
        outResult << "\n";
    }

    return 0;
}