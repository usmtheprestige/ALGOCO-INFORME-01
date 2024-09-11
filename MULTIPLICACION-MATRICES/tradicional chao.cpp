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

// Función para multiplicar dos matrices
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();
    
    // Matriz de resultado
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    // Algoritmo cúbico tradicional
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
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
    bool is_square = true;  // Cambia a 'true' si deseas multiplicar matrices cuadradas, 'false' para no cuadradas

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
        // Multiplicar matrices no cuadradas (modificado para pedir archivos manualmente)
        string fileA = "naDISP729x64.txt";
        string fileB = "naDISP64x256.txt";

        // Lee las matrices A y B desde los archivos proporcionados
        vector<vector<int>> A = readMatrixFromFile(fileA);
        vector<vector<int>> B = readMatrixFromFile(fileB);

        // Asegurarse de que las matrices sean conformables para multiplicación
        if (A[0].size() != B.size()) {
            cout << "Error: Las matrices no son conformables para la multiplicación." << endl;
            return 1;
        }

        // Mide el tiempo de ejecución
        auto start = high_resolution_clock::now();  // Inicia la medición de tiempo

        vector<vector<int>> result = matrixMultiply(A, B);  // Multiplicación de matrices

        auto end = high_resolution_clock::now();  // Finaliza la medición de tiempo
        auto duration = duration_cast<microseconds>(end - start);  // Calcula la duración en microsegundos

        // Imprime el tiempo de ejecución
        cout << "Multiplicación de matrices no cuadradas: " << duration.count() << " microsegundos" << endl;
    }

    return 0;
}
