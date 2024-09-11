#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Lee el array desde el archivo
vector<int> readArrayFromFile(const string& filename) {
    ifstream infile(filename);
    vector<int> arr;
    int value;

    while (infile >> value) {
        arr.push_back(value);
    }

    infile.close();
    return arr;
}

int main() {
    vector<int> arr = {10, 32, 100, 316, 1000, 3162, 10000, 31622, 100000};

    // Iterar sobre los tamaños
    for (int elemento : arr) {
        
        vector<int> arreglo = readArrayFromFile("DES" + to_string(elemento) + ".txt");
        // "DES" también puede ser "DESr", "INV", "ORD", "SEM" o "SEMr",
        // dependiendo del tipo de arreglo que se quiera usar

        auto start = high_resolution_clock::now(); // Inicia la medición de tiempo

        sort(arreglo.begin(), arreglo.end());  // Usa la función std::sort (Introsort)

        auto end = high_resolution_clock::now(); // Finaliza la medición de tiempo

        auto duration = duration_cast<microseconds>(end - start); // Calcula la duración en microsegundos

        cout << duration.count() <<  endl;
    }

    return 0;
}
