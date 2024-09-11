#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

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

        quickSort(arreglo, 0, arreglo.size() - 1);

        auto end = high_resolution_clock::now(); // Finaliza la medición de tiempo

        auto duration = duration_cast<microseconds>(end - start); // Calcula la duración en microsegundos

        cout << duration.count() << endl;
    }

    return 0;
}
