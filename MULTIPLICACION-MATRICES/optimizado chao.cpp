#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo .txt
vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream infile(filename);
    vector<vector<int>> matrix;
    string line;

    while (getline(infile, line)) {
        istringstream iss(line);
        vector<int> row;
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    infile.close();
    return matrix;
}

// Función para transponer una matriz
vector<vector<int>> transposeMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> transposed(cols, vector<int>(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}


// Función para multiplicar dos matrices con transposición de la segunda matriz
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();
    
    // Transponer la matriz B para mejorar la localidad de los datos
    vector<vector<int>> B_transposed = transposeMatrix(B);

    // Matriz de resultado
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    // Algoritmo cúbico iterativo optimizado
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B_transposed[j][k];
            }
        }
    }

    return result;
}


// Función para imprimir una matriz (opcional, para visualizar los resultados)
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}



int main() {
    string tipo = "ID";  // Cambia aquí el tipo de matriz (DISP, DEN, ID)
    cout << tipo << endl;

    // Escoge si deseas multiplicar matrices cuadradas o no cuadradas
    bool is_square = false;  // Cambia a 'true' si deseas multiplicar matrices cuadradas, 'false' para no cuadradas

    if (is_square) {
        // Multiplicar matrices cuadradas (este código se mantiene igual)
        vector<int> square_sizes = {4, 9, 16, 64, 81, 256, 729, 1024};
        for (int size : square_sizes) {
            vector<vector<int>> A = readMatrixFromFile("qaDEN" + to_string(size) + "x" + to_string(size) + ".txt");
            vector<vector<int>> B = readMatrixFromFile("qb" + tipo + to_string(size) + "x" + to_string(size) + ".txt");

            auto start = high_resolution_clock::now();  // Inicia la medición de tiempo

            vector<vector<int>> result = matrixMultiply(A, B);  // Multiplicación de matrices

            auto end = high_resolution_clock::now();  // Finaliza la medición de tiempo
            auto duration = duration_cast<microseconds>(end - start);  // Calcula la duración en microsegundos

            // Imprime el tiempo de ejecución
            cout << duration.count() << endl;
        }
        } else {
        // Pares de archivos para matrices no cuadradas
        vector<pair<string, string>> file_pairs = {
            {"naDEN9x4.txt", "naDEN4x16.txt"},
            {"naDEN4x16.txt", "naDEN16x64.txt"},
            {"naDEN81x16.txt", "naDEN16x64.txt"},
            {"naDEN16x64.txt", "naDEN64x256.txt"},
            {"naDEN729x64.txt", "naDEN64x256.txt"},
            {"naDISP9x4.txt", "naDISP4x16.txt"},
            {"naDISP4x16.txt", "naDISP16x64.txt"},
            {"naDISP81x16.txt", "naDISP16x64.txt"},
            {"naDISP16x64.txt", "naDISP64x256.txt"},
            {"naDISP729x64.txt", "naDISP64x256.txt"}
        };

        for (const auto& [fileA, fileB] : file_pairs) {
            cout << "Multiplicando " << fileA << " y " << fileB << endl;
            
            // Lee las matrices A y B desde los archivos
            vector<vector<int>> A = readMatrixFromFile(fileA);
            vector<vector<int>> B = readMatrixFromFile(fileB);

            // Asegurarse de que las matrices sean conformables para multiplicación
            if (A[0].size() != B.size()) {
                cout << "Error: Las matrices no son conformables para la multiplicación." << endl;
                continue;
            }

            // Mide el tiempo de ejecución
            auto start = high_resolution_clock::now();  // Inicia la medición de tiempo

            vector<vector<int>> result = matrixMultiply(A, B);  // Multiplicación de matrices

            auto end = high_resolution_clock::now();  // Finaliza la medición de tiempo
            auto duration = duration_cast<microseconds>(end - start);  // Calcula la duración en microsegundos

            // Imprime el tiempo de ejecución
            cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;
        }
    }

    return 0;
}
