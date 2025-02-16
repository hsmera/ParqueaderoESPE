#include "CuadradoLatino.h"
#include "Validaciones.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <random> 
#include <set>

using namespace std;

// Constructor
CuadradoLatino::CuadradoLatino(int tam) : tamanio(tam) {
    cuadrado.resize(tamanio, vector<int>(tamanio, 0));
}

void CuadradoLatino::ingresarNumeros() {
    cout << "Ingrese " << tamanio * tamanio << " numeros para construir el Cuadrado Latino:\n";

    vector<int> numerosIngresados;  
    numerosIngresados.reserve(tamanio * tamanio);  

    // Ingresar los números
    for (int i = 0; i < tamanio * tamanio; i++) {
        int num;
        cout << "Numero [" << i + 1 << "]: ";
        cin >> num;
        numerosIngresados.push_back(num);
    }

    // Ordenar los números para formar un Cuadrado Latino válido
    organizarCuadrado(numerosIngresados);

    // Mostrar el cuadrado generado
    cout << "Cuadrado Latino generado:\n";
    imprimir();
}

void CuadradoLatino::organizarCuadrado(vector<int>& numeros) {
    int n = tamanio;

    // Crear un set para saber qué números han sido usados en cada fila y columna
    vector<set<int>> usadoFila(n);
    vector<set<int>> usadoColumna(n);
    vector<vector<int>> tempCuadrado(n, vector<int>(n, 0));

    // Intentamos colocar los números asegurando que no se repitan en filas o columnas
    int idx = 0;
    bool exito = false;
    
    while (!exito) {
        exito = true;
        usadoFila = vector<set<int>>(n);
        usadoColumna = vector<set<int>>(n);
        tempCuadrado = vector<vector<int>>(n, vector<int>(n, 0));
        idx = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int num = numeros[idx++];

                // Si el número ya está en la fila o en la columna, el intento es inválido
                if (usadoFila[i].count(num) || usadoColumna[j].count(num)) {
                    exito = false;
                    break;
                }

                tempCuadrado[i][j] = num;
                usadoFila[i].insert(num);
                usadoColumna[j].insert(num);
            }
            if (!exito) break;
        }

        if (!exito) {
            // Si no se logra generar un cuadrado latino, mezclamos los números y probamos de nuevo
            random_shuffle(numeros.begin(), numeros.end());
        }
    }

    cuadrado = tempCuadrado;
}

// Opción 2: Generar números con incremento
void CuadradoLatino::generarNumeros(int inicio, int incremento) {
    cout << "Generando numeros con inicio " << inicio << " y incremento " << incremento << endl;

    vector<int> numerosGenerados;
    int num = inicio;

    for (int i = 0; i < tamanio * tamanio; i++) {
        numerosGenerados.push_back(num);
        num += incremento;
    }

    organizarCuadrado(numerosGenerados); // Reutilizar la lógica para organizar los números

    // Mostrar el cuadrado generado
    cout << "Cuadrado generado:\n";
    imprimir();
}

// Imprimir el Cuadrado Latino
void CuadradoLatino::imprimir() {
    cout << "\n==== Cuadrado Latino ====\n";

    for (const auto& fila : cuadrado) {
        for (int num : fila) {
            cout << setw(4) << num << " ";
        }
        cout << endl;
    }
}
