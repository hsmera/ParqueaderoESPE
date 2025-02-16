#ifndef CUADRADO_MAGICO_H
#define CUADRADO_MAGICO_H

#include <vector>
#include <iostream>

using namespace std;

class CuadradoMagico {
private:
    int tamanio;
    vector<vector<int>> cuadrado;
    vector<int> numeros; 

public:
    CuadradoMagico(int tam);
    void ingresarNumeros();
    void generarNumeros(int inicio, int incremento);
    void generarCuadrado();
    void generarCuadradoImpar();
    void generarCuadradoParDoble();
    void generarCuadradoParSimple();
    void imprimir();
};

#endif
