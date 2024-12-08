#ifndef ESPACIOPARQUEADERO_H
#define ESPACIOPARQUEADERO_H

#include <string>
#include <ctime>
#include <iostream>
using namespace std;

struct Nodo {
    string id;         // Identificador del espacio (01-12)
    bool ocupado;      // Estado del espacio (true = ocupado, false = libre)
    string placa;      // Placa del auto estacionado (vacío si está libre)
    time_t horaIngreso; // Tiempo de ingreso (0 si está libre)
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const string& id)
        : id(id), ocupado(false), placa(""), horaIngreso(0), siguiente(nullptr), anterior(nullptr) {}
};

class EspacioParqueadero {
public:
    Nodo* crearEspacio(const string& id);
    void ocuparEspacio(Nodo* espacio, const string& placa);
    void liberarEspacio(Nodo* espacio);
    string obtenerEstado(const Nodo* espacio) const;
};

#endif // ESPACIOPARQUEADERO_H
