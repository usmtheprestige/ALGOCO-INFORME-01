#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;



void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


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

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {10, 32, 100, 316, 1000, 3162, 10000, 31622, 100000};

    // Random
    for (int elemento : arr) {
        
        vector<int> arreglo = readArrayFromFile("DES" + to_string(elemento) + ".txt");
        // "DES" también puede ser "DESr", "INV", "ORD", "SEM" o "SEMr",
        // dependiendo del tipo de arreglo que se quiera usar

        auto start = high_resolution_clock::now(); // Inicia la medición de tiempo

        bubbleSort(arreglo);

        auto end = high_resolution_clock::now(); // Finaliza la medición de tiempo

        auto duration = duration_cast<microseconds>(end - start); // Calcula la duración en nanosegundos

        cout << duration.count() << endl;
    }

    return 0;
}
