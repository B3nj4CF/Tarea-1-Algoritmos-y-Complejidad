/**
 * TAREA 1 - INF-221 ALGORITMOS Y COMPLEJIDAD
 * Estudiante: [Tu Nombre]
 * Universidad Técnica Federico Santa María
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <unistd.h> // Para obtener tamaño de página si fuera necesario

typedef std::vector<std::vector<int>> Matrix;

// Prototipos
Matrix multiplyNaive(const Matrix& M1, const Matrix& M2, int n);
Matrix strassen(const Matrix& A, const Matrix& B, int n);

/**
 * Lee la memoria máxima (VmPeak) que ha usado el proceso actual en KB.
 * Esto es ideal para sistemas Linux (Arch).
 */
long getMemoryUsage() {
    std::ifstream statusFile("/proc/self/status");
    std::string line;
    while (std::getline(statusFile, line)) {
        if (line.find("VmPeak:") != std::string::npos) {
            // Extrae el número de la línea "VmPeak:   12345 kB"
            return std::stol(line.substr(line.find_first_of("0123456789")));
        }
    }
    return 0;
}

Matrix readMatrix(std::string filename, int n) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir: " << filename << std::endl;
        exit(1);
    }
    Matrix mat(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> mat[i][j];
        }
    }
    return mat;
}

/**
 * Guarda tiempo y memoria en la ruta especificada por tu imagen:
 * code/matrix_multiplication/data/measurements/
 */
void saveMetrics(std::string algo, int n, double time, long memory) {
    std::string path = "data/measurements/" + algo + "_" + std::to_string(n) + "_metrics.txt";
    std::ofstream outFile(path, std::ios::app);
    if (outFile.is_open()) {
        // Guardamos: Tiempo(s) Memoria(KB)
        outFile << time << " " << memory << "\n";
        outFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Uso: ./matrix_test <n> <algoritmo> <file1> <file2>\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    std::string algo = argv[2];
    std::string f1 = argv[3];
    std::string f2 = argv[4];

    Matrix M1 = readMatrix(f1, n);
    Matrix M2 = readMatrix(f2, n);
    Matrix result;

    // --- MEDICIÓN DE TIEMPO ---
    auto start = std::chrono::high_resolution_clock::now();

    if (algo == "naive") {
        result = multiplyNaive(M1, M2, n);
    } else if (algo == "strassen") {
        result = strassen(M1, M2, n);
    } else {
        std::cerr << "Algoritmo no reconocido: " << algo << "\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    // --- MEDICIÓN DE MEMORIA ---
    long memUsed = getMemoryUsage();

    // Guardar en data/measurements/
    saveMetrics(algo, n, diff.count(), memUsed);

    // --- GUARDAR MATRIZ RESULTANTE ---
    // Según tu imagen: data/matrix_output/
    std::string outPath = "data/matrix_output/" + std::to_string(n) + "_" + algo + "_out.txt";
    std::ofstream outResult(outPath);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outResult << result[i][j] << (j == n - 1 ? "" : " ");
        }
        outResult << "\n";
    }

    return 0;
}