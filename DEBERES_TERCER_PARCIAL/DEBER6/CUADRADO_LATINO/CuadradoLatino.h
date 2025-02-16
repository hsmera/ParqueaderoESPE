#ifndef CUADRADO_LATINO_H
#define CUADRADO_LATINO_H

#include <vector>  // Agregar esta línea
#include <iostream>

using namespace std;

class CuadradoLatino {
private:
    int tamanio;
    vector<vector<int>> cuadrado;

public:
    CuadradoLatino(int tam);
    void ingresarNumeros();
    void generarNumeros(int inicio, int incremento);
    void imprimir();
    
    void organizarCuadrado(vector<int>& numeros); 
};

#endif
