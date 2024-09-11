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


vector<vector<int>> padMatrixToPowerOfTwo(const vector<vector<int>>& matrix) {
    int originalRows = matrix.size();
    int originalCols = matrix[0].size();

    int newSize = 1;
    while (newSize < max(originalRows, originalCols)) {
        newSize *= 2;
    }

    vector<vector<int>> padded(newSize, vector<int>(newSize, 0));

    for (int i = 0; i < originalRows; ++i) {
        for (int j = 0; j < originalCols; ++j) {
            padded[i][j] = matrix[i][j];
        }
    }

    return padded;
}

vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n <= 1) {
        vector<vector<int>> result(1, vector<int>(1, A[0][0] * B[0][0]));
        return result;
    }

    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    vector<vector<int>> M1 = strassenMultiply(add(A11, A22), add(B11, B22));
    vector<vector<int>> M2 = strassenMultiply(add(A21, A22), B11);
    vector<vector<int>> M3 = strassenMultiply(A11, subtract(B12, B22));
    vector<vector<int>> M4 = strassenMultiply(A22, subtract(B21, B11));
    vector<vector<int>> M5 = strassenMultiply(add(A11, A12), B22);
    vector<vector<int>> M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
    vector<vector<int>> M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

    vector<vector<int>> C11 = add(subtract(add(M1, M4), M5), M7);
    vector<vector<int>> C12 = add(M3, M5);
    vector<vector<int>> C21 = add(M2, M4);
    vector<vector<int>> C22 = add(subtract(add(M1, M3), M2), M6);

    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            result[i][j] = C11[i][j];
            result[i][j + newSize] = C12[i][j];
            result[i + newSize][j] = C21[i][j];
            result[i + newSize][j + newSize] = C22[i][j];
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

    bool is_square = true;  // Cambia a 'true' si deseas multiplicar matrices cuadradas, 'false' para no cuadradas

    if (is_square) {
        vector<int> square_sizes = {4, 9, 16, 64, 81, 256, 729, 1024};
        for (int size : square_sizes) {
            vector<vector<int>> A = readMatrixFromFile("qaDEN" + to_string(size) + "x" + to_string(size) + ".txt");
            vector<vector<int>> B = readMatrixFromFile("qb" + tipo + to_string(size) + "x" + to_string(size) + ".txt");

            // Asegurarse de que las matrices sean cuadradas y rellenas a tamaño potencia de 2
            A = padMatrixToPowerOfTwo(A);
            B = padMatrixToPowerOfTwo(B);

            auto start = high_resolution_clock::now();

            vector<vector<int>> result = strassenMultiply(A, B);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);

            cout << duration.count() << endl;
        }
    } else {
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

            vector<vector<int>> A = readMatrixFromFile(fileA);
            vector<vector<int>> B = readMatrixFromFile(fileB);

            // Asegurarse de que las matrices sean conformables para la multiplicación
            if (A[0].size() != B.size()) {
                cout << "Error: Las matrices no son conformables para la multiplicación." << endl;
                continue;
            }

            // Asegurarse de que las matrices sean cuadradas y rellenas a tamaño potencia de 2
            A = padMatrixToPowerOfTwo(A);
            B = padMatrixToPowerOfTwo(B);

            auto start = high_resolution_clock::now();

            vector<vector<int>> result = strassenMultiply(A, B);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);

            cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;
        }
    }

    return 0;
}