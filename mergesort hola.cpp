#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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

        mergeSort(arreglo, 0, arreglo.size() - 1);

        auto end = high_resolution_clock::now(); // Finaliza la medición de tiempo

        auto duration = duration_cast<microseconds>(end - start); // Calcula la duración en microsegundos

        cout << duration.count() << endl;
    }

    return 0;
}
