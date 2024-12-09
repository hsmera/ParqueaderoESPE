/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include "EspacioParqueadero.h"
#include <vector>
#include <fstream>
#include <sstream>

class Parqueadero {
private:
    Nodo* head; // Nodo inicial de la lista doblemente enlazada circular
    EspacioParqueadero manejadorEspacios;
    const int capacidad = 12;
    const string archivoParqueadero = "parqueadero.txt";

    void inicializarEspacios();
    void cargarDesdeArchivo();
    void guardarEnArchivo();

public:
    Parqueadero();
    ~Parqueadero();

    void mostrarEstado() const;
    bool estacionarAuto(const string& placa, const string& espacioId);
    bool retirarAuto(const string& placa);
};

#endif // PARQUEADERO_H
