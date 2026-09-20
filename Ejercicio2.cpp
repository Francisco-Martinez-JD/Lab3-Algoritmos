#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& A, int p, int r) {
    for (int i = p + 1; i <= r; i++) {
        int key = A[i];
        int j = i - 1;

        while (j >= p && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void merge(vector<int>& A, vector<int>& buffer, int p, int q, int r) {

    for (int t = p; t <= r; t++) {
        buffer[t] = A[t];
    }

    int i = p;       
    int j = q + 1;    
    int k = p;        

    while (i <= q && j <= r) {
        if (buffer[i] <= buffer[j]) {
            A[k++] = buffer[i++];
        } else {
            A[k++] = buffer[j++];
        }
    }
    while (i <= q) A[k++] = buffer[i++];
    while (j <= r) A[k++] = buffer[j++];
}

void hybridMergeSort(vector<int>& A, vector<int>& buffer, int p, int r, int umbral_k) {
    if (r - p + 1 <= umbral_k) {
        insertionSort(A, p, r);
    } else if (p < r) {
        int q = p + (r - p) / 2;

        hybridMergeSort(A, buffer, p, q, umbral_k);
        hybridMergeSort(A, buffer, q + 1, r, umbral_k);

        merge(A, buffer, p, q, r);
    }
}

int main() {
    int n = 1000000;
    vector<int> arreglo_original(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);

    for (int i = 0; i < n; i++) {
        arreglo_original[i] = dis(gen);
    }

    vector<int> ks = {1, 2, 4, 8, 16, 32, 64, 128};
    vector<int> buffer(n);

    cout << "k,tiempo_us\n";

    for (int k : ks) {
        vector<int> A = arreglo_original;

        auto inicio = high_resolution_clock::now();
        hybridMergeSort(A, buffer, 0, n - 1, k);
        auto fin = high_resolution_clock::now();

        auto duracion = duration_cast<microseconds>(fin - inicio);

        cout << k << "," << duracion.count() << "\n";
    }

    return 0;
}