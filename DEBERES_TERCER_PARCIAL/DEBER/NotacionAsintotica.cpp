#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <conio.h>      
#include <algorithm>

using namespace std;
using namespace std::chrono;

// --------------------- Funciones de Algoritmos -----------------------------

// Función de Bubble Sort (con optimización: sale si no hay intercambios)
void bubbleSort(vector<int>& arr) {
    bool swapped;
    for (size_t i = 0; i < arr.size()-1; i++) {
        swapped = false;
        for (size_t j = 0; j < arr.size()-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Función auxiliar para Merge Sort: fusiona dos subarreglos
void merge(vector<int>& arr, int left, int mid, int right) {
    int i = left, j = mid+1;
    vector<int> temp;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) {
        temp.push_back(arr[i++]);
    }
    while (j <= right) {
        temp.push_back(arr[j++]);
    }
    for (int k = left; k <= right; k++) {
        arr[k] = temp[k - left];
    }
}

// Merge Sort recursivo
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

// Función de búsqueda binaria (iterativa)
int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size()-1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // no encontrado
}

// --------------------- Demostraciones con Medición -----------------------------

// Demostración O(1): Acceso a un elemento del arreglo
void demoO1() {
    cout << "Demostracion de O(1): Acceso a un elemento del arreglo\n";
    const int size = 1000000;
    vector<int> arr(size, 42); // arreglo con 1 millón de elementos

    // Usamos 'volatile' para evitar que el compilador optimice el acceso
    volatile int dummy;  
    int iterations = 100000000; // muchas iteraciones para acumular tiempo

    // Best-case: acceso al primer elemento
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        dummy = arr[0];
    }
    auto end = high_resolution_clock::now();
    auto duration_best = duration_cast<microseconds>(end - start).count();

    // Worst-case: acceso al último elemento
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        dummy = arr[size - 1];
    }
    end = high_resolution_clock::now();
    auto duration_worst = duration_cast<microseconds>(end - start).count();

    // Average-case: acceso al elemento central
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        dummy = arr[size / 2];
    }
    end = high_resolution_clock::now();
    auto duration_avg = duration_cast<microseconds>(end - start).count();

    cout << "\nAcceso O(1) - Teorico:\n"
         << "  Big-O: O(1), Omega: Ω(1), Theta: Θ(1)\n";
    cout << "Tiempo Best-case (primer elemento): " << duration_best << " microsegundos\n";
    cout << "Tiempo Worst-case (último elemento): " << duration_worst << " microsegundos\n";
    cout << "Tiempo Average-case (elemento central): " << duration_avg << " microsegundos\n";
}

// Demostración O(log n): Búsqueda Binaria
void demoOlogN() {
    cout << "Demostracion de O(log n): Busqueda Binaria en arreglo ordenado\n";
    const int size = 1000000;
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i; // arreglo ordenado
    }

    int iterations = 100000; // repeticiones para medir el tiempo
    int index;

    // Best-case: el elemento buscado es el del medio (se encuentra en la primera comparacion)
    int target_best = arr[size/2];
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        index = binarySearch(arr, target_best);
    }
    auto end = high_resolution_clock::now();
    auto duration_best = duration_cast<microseconds>(end - start).count();

    // Worst-case: elemento no existe (se recorre el máximo de comparaciones)
    int target_worst = -1; // no existe en el arreglo
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        index = binarySearch(arr, target_worst);
    }
    end = high_resolution_clock::now();
    auto duration_worst = duration_cast<microseconds>(end - start).count();

    // Average-case: elemento aleatorio dentro del arreglo
    srand(time(0));
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        int target_avg = arr[rand() % size];
        index = binarySearch(arr, target_avg);
    }
    end = high_resolution_clock::now();
    auto duration_avg = duration_cast<microseconds>(end - start).count();

    cout << "\nBusqueda Binaria - Teorico:\n"
         << "  Big-O: O(log n), Omega: Ω(1) (si el elemento es el del medio), Theta: Θ(log n)\n";
    cout << "Tiempo Best-case (elemento central): " << duration_best << " microsegundos\n";
    cout << "Tiempo Worst-case (elemento no existe): " << duration_worst << " microsegundos\n";
    cout << "Tiempo Average-case (elemento aleatorio): " << duration_avg << " microsegundos\n";
}

// Demostración O(n): Suma de los elementos del arreglo
void demoOn() {
    cout << "Demostracion de O(n): Suma de los elementos del arreglo\n";
    const int size = 10000000;
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = 1; // llenamos el arreglo con 1's
    }

    long long sum = 0;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "\nSuma de elementos - Teorico:\n"
         << "  Big-O: O(n), Omega: Ω(n), Theta: Θ(n)\n";
    cout << "Suma: " << sum << "\n";
    cout << "Tiempo de ejecucion: " << duration << " milisegundos\n";
}

// Demostración O(n log n): Merge Sort
void demoOnlogN() {
    cout << "Demostracion de O(n log n): Merge Sort\n";
    const int size = 100000; // tamaño moderado

    // Best-case: arreglo ya ordenado
    vector<int> arr_best(size);
    for (int i = 0; i < size; i++) {
        arr_best[i] = i;
    }
    auto start = high_resolution_clock::now();
    mergeSort(arr_best, 0, size-1);
    auto end = high_resolution_clock::now();
    auto duration_best = duration_cast<milliseconds>(end - start).count();

    // Worst-case: arreglo en orden inverso
    vector<int> arr_worst(size);
    for (int i = 0; i < size; i++) {
        arr_worst[i] = size - i;
    }
    start = high_resolution_clock::now();
    mergeSort(arr_worst, 0, size-1);
    end = high_resolution_clock::now();
    auto duration_worst = duration_cast<milliseconds>(end - start).count();

    // Average-case: arreglo con valores aleatorios
    vector<int> arr_avg(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr_avg[i] = rand() % size;
    }
    start = high_resolution_clock::now();
    mergeSort(arr_avg, 0, size-1);
    end = high_resolution_clock::now();
    auto duration_avg = duration_cast<milliseconds>(end - start).count();

    cout << "\nMerge Sort - Teorico:\n"
         << "  Big-O:(n log n), Omega:(n log n), Theta:(n log n)\n";
    cout << "Tiempo Mejor Caso (arreglo ordenado): " << duration_best << " milisegundos\n";
    cout << "Tiempo Peor Caso (arreglo en orden inverso): " << duration_worst << " milisegundos\n";
    cout << "Tiempo Caso Promedio (arreglo aleatorio): " << duration_avg << " milisegundos\n";
}

// Demostración O(n^2): Bubble Sort
void demoOn2() {
    cout << "Demostracion de O(n^2): Bubble Sort\n";
    const int size = 1000; // tamaño pequeño por la complejidad cuadratica

    // Best-case: arreglo ya ordenado
    vector<int> arr_best(size);
    for (int i = 0; i < size; i++) {
        arr_best[i] = i;
    }
    auto start = high_resolution_clock::now();
    bubbleSort(arr_best);
    auto end = high_resolution_clock::now();
    auto duration_best = duration_cast<milliseconds>(end - start).count();

    // Worst-case: arreglo en orden inverso
    vector<int> arr_worst(size);
    for (int i = 0; i < size; i++) {
        arr_worst[i] = size - i;
    }
    start = high_resolution_clock::now();
    bubbleSort(arr_worst);
    end = high_resolution_clock::now();
    auto duration_worst = duration_cast<milliseconds>(end - start).count();

    // Average-case: arreglo con valores aleatorios
    vector<int> arr_avg(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr_avg[i] = rand() % size;
    }
    start = high_resolution_clock::now();
    bubbleSort(arr_avg);
    end = high_resolution_clock::now();
    auto duration_avg = duration_cast<milliseconds>(end - start).count();

    cout << "\nBubble Sort - Teorico:\n"
         << "  Big-O: O(n^2), Omega: Ω(n) (si se optimiza la deteccion de ordenado), Theta: Θ(n^2)\n";
    cout << "Tiempo Mejor Caso (arreglo ordenado): " << duration_best << " milisegundos\n";
    cout << "Tiempo Peor Caaso (arreglo en orden inverso): " << duration_worst << " milisegundos\n";
    cout << "Tiempo Caso Promedio (arreglo aleatorio): " << duration_avg << " milisegundos\n";
}

// --------------------- Menu Interactivo -----------------------------

int main() {
    // Semilla para números aleatorios
    srand(time(0));

    vector<string> options = {
        "O(1) - Acceso a un elemento del arreglo",
        "O(log n) - Busqueda Binaria",
        "O(n) - Suma de elementos del arreglo",
        "O(n log n) - Merge Sort",
        "O(n^2) - Bubble Sort",
        "Salir"
    };

    int selected = 0;
    int optionCount = options.size();

    while (true) {
        system("cls"); // Limpia la pantalla (Windows)
        cout << "Menu de demostracion de notacion asintotica\n\n";
        for (int i = 0; i < optionCount; i++) {
            if (i == selected)
                cout << "-> " << options[i] << "\n";
            else
                cout << "   " << options[i] << "\n";
        }

        int ch = _getch();
        if (ch == 224) { // Código inicial para teclas de flecha
            ch = _getch();
            if (ch == 72) { // Flecha arriba
                selected = (selected - 1 + optionCount) % optionCount;
            } else if (ch == 80) { // Flecha abajo
                selected = (selected + 1) % optionCount;
            }
        } else if (ch == 13) { // Enter
            system("cls");
            if (selected == optionCount - 1) {
                cout << "Saliendo...\n";
                break;
            }
            switch (selected) {
                case 0: demoO1(); break;
                case 1: demoOlogN(); break;
                case 2: demoOn(); break;
                case 3: demoOnlogN(); break;
                case 4: demoOn2(); break;
            }
            cout << "\nPresione cualquier tecla para volver al menu...";
            _getch();
        }
    }
    return 0;
}
