/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

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
