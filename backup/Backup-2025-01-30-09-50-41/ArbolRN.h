#ifndef ARBOLRN_H
#define ARBOLRN_H

#include "NodoRN.h"
#include <iostream>
#include <vector>
using namespace std;

class ArbolRN {
private:
    NodoRN* raiz;             // Raíz del árbol
    NodoRN* nulo;             // Nodo nulo para representar hojas vacías

    // Métodos auxiliares
    void rotarIzquierda(NodoRN* x);
    void rotarDerecha(NodoRN* y);
    void balancearInsercion(NodoRN* nodo);
    void balancearEliminacion(NodoRN* nodo);
    void eliminarNodo(NodoRN* nodo);

    void recorridoInOrden(NodoRN* nodo, vector<NodoRN*>& nodos) const;

    NodoRN* buscarNodo(NodoRN* nodo, const string& placa) const;

public:
    // Constructor
    ArbolRN();

    // Operaciones principales
    void insertar(const string& placa, const string& espacioId, const string& fechaHoraIngreso, const string& fechaHoraSalida = "");
    void eliminar(const string& placa);
    NodoRN* buscar(const string& placa) const;

    // Recorrido
    vector<NodoRN*> obtenerInOrden() const;

    // Destructor
    ~ArbolRN();
};

#endif
