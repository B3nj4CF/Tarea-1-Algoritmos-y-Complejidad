#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>

typedef std::vector<std::vector<int>> Matrix;

// Prototipos de funciones de multiplicacion (implementadas en naive.cpp y strassen.cpp)
Matrix multiplyNaive(const Matrix& M1, const Matrix& M2, int n);
Matrix strassen(const Matrix& A, const Matrix& B, int n);

/**
 * Lee una matriz cuadrada de tamaño n desde un archivo.
 * Según el anexo A.2, los archivos siguen el formato {n}_{t}_{d}_{m}_1.txt.
 */
Matrix readMatrix(std::string filename, int n) {
    std::ifstream file(filename);
    Matrix mat(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> mat[i][j];
        }
    }
    return mat;
}

/**
 * Guarda el tiempo de ejecución en la carpeta measurements/matrix_multiplication.
 */
void saveResult(std::string algorithm, std::string testCase, double duration) {
    std::ofstream outFile("measurements/matrix_multiplication/" + algorithm + "_" + testCase + ".txt", std::ios::app);
    outFile << duration << "\n";
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: ./matrix_multiplication <n> <algoritmo> <archivo_M1> <archivo_M2>\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    std::string algo = argv[2];
    std::string file1 = argv[3];
    std::string file2 = argv[4];

    // 1. Cargar las matrices de entrada
    Matrix M1 = readMatrix(file1, n);
    Matrix M2 = readMatrix(file2, n);
    Matrix result;

    // 2. Medir tiempo de ejecución con chrono
    auto start = std::chrono::high_resolution_clock::now();

    if (algo == "naive") {
        result = multiplyNaive(M1, M2, n);
    } else if (algo == "strassen") {
        result = strassen(M1, M2, n);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    // 3. Guardar medición de tiempo 
    saveResult(algo, "n" + std::to_string(n), diff.count());

    // 4. Escribir la matriz resultante en el archivo de salida indicado en el anexo [cite: 117]
    // El nombre del archivo de salida debe ser {n}_{t}_{d}_{m}_out.txt[cite: 117].
    std::string outFileName = "output_matrix.txt"; // Ajustar según el loop de pruebas
    std::ofstream outResult(outFileName);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outResult << result[i][j] << (j == n - 1 ? "" : " ");
        }
        outResult << "\n";
    }

    return 0;
}