#include "CuadradoMagico.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <unordered_set>
#include "Validaciones.h"

using namespace std;

CuadradoMagico::CuadradoMagico(int tam) : tamanio(tam) {
    cuadrado.resize(tamanio, vector<int>(tamanio, 0));
}

// Opción 1: Ingresar números manualmente
void CuadradoMagico::ingresarNumeros() {
    numeros.clear();
    unordered_set<int> usados;

    cout << "Ingrese " << tamanio * tamanio << " numeros distintos\n";
    while (numeros.size() < tamanio * tamanio) {
        Validaciones<int> validador;
        int num;
        num = validador.ingresar("Ingrese los numeros separados por un Enter: ", "entero");
        cout << endl;

        if (usados.find(num) != usados.end()) {
            cout << "El numero " << num << " ya fue ingresado. Intente otro.\n";
        } else {
            numeros.push_back(num);
            usados.insert(num);
        }
    }
}

// Opción 2: Generar números con incremento
void CuadradoMagico::generarNumeros(int inicio, int incremento) {
    if (incremento == 0) {
        cout << "El incremento no puede ser 0. Intente de nuevo.\n";
        return;
    }

    numeros.clear();  // Asegurar que la lista esté vacía antes de llenarla

    for (int i = 0; i < tamanio * tamanio; i++) {
        numeros.push_back(inicio + i * incremento);
    }

    sort(numeros.begin(), numeros.end());  // Ordenar los números para evitar desorden
}

// Método para decidir qué algoritmo de generación usar
void CuadradoMagico::generarCuadrado() {
    // Reiniciar la matriz antes de llenarla
    cuadrado.assign(tamanio, vector<int>(tamanio, 0));

    if (tamanio % 2 != 0) {
        generarCuadradoImpar();
    } else if (tamanio % 4 == 0) {
        generarCuadradoParDoble();
    } else {
        generarCuadradoParSimple();
    }
}

// Algoritmo siamés (sólo para impares)
void CuadradoMagico::generarCuadradoImpar() {
    int fila = 0, columna = tamanio / 2;

    for (int i = 0; i < numeros.size(); i++) {
        cuadrado[fila][columna] = numeros[i];

        int nuevaFila = (fila - 1 + tamanio) % tamanio;
        int nuevaColumna = (columna + 1) % tamanio;

        if (cuadrado[nuevaFila][nuevaColumna] != 0) {
            fila = (fila + 1) % tamanio;
        } else {
            fila = nuevaFila;
            columna = nuevaColumna;
        }
    }
}

// Algoritmo para pares dobles (n % 4 == 0)
void CuadradoMagico::generarCuadradoParDoble() {
    int n = tamanio;
    vector<vector<int>> temp(n, vector<int>(n));
    int valor = 0;  // Cambié el inicio a 0 para usar los números generados

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] = numeros[valor++];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (((i % 4 == j % 4) || ((i % 4 + j % 4) == 3))) {
                cuadrado[i][j] = temp[n - i - 1][n - j - 1];
            } else {
                cuadrado[i][j] = temp[i][j];
            }
        }
    }
}

// Algoritmo para pares simples (n % 4 != 0)
void CuadradoMagico::generarCuadradoParSimple() {
    int mitad = tamanio / 2;
    int subCuadrado = mitad * mitad;

    CuadradoMagico subCM(mitad);
    subCM.generarNumeros(numeros[0], (numeros[1] - numeros[0]));  // Asegurar consistencia
    subCM.generarCuadradoImpar();
    vector<vector<int>> sub = subCM.cuadrado;

    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            cuadrado[i][j] = sub[i][j];
            cuadrado[i + mitad][j + mitad] = sub[i][j] + 2 * subCuadrado;
            cuadrado[i][j + mitad] = sub[i][j] + 3 * subCuadrado;
            cuadrado[i + mitad][j] = sub[i][j] + subCuadrado;
        }
    }

    int k = (tamanio - 2) / 4;
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < k; j++) {
            swap(cuadrado[i][j], cuadrado[i + mitad][j]);
            swap(cuadrado[i][j + mitad - k], cuadrado[i + mitad][j + mitad - k]);
        }
    }
}

// Imprimir el cuadrado mágico
void CuadradoMagico::imprimir() {
    cout << "\nCuadrado magico generado:\n";
    for (const auto &fila : cuadrado) {
        for (int num : fila) {
            cout << setw(4) << num << "\t";
        }
        cout << endl;
    }
}
