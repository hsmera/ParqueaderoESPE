#ifndef ESPACIOPARQUEADERO_H
#define ESPACIOPARQUEADERO_H

#include "Nodo.h" // Incluir el archivo Nodo.h
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

class EspacioParqueadero {
public:
    Nodo* crearEspacio(const string& id);
    void ocuparEspacio(Nodo* espacio, const string& placa);
    void liberarEspacio(Nodo* espacio);
    string obtenerEstado(const Nodo* espacio) const;
};

#endif // ESPACIOPARQUEADERO_H
