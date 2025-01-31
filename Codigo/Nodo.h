/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#ifndef NODO_H
#define NODO_H

#include <string>
#include <ctime>
using namespace std;

class Nodo {
public:
    string id;          
    bool ocupado;       
    string placa;       
    time_t horaIngreso; // Tiempo de ingreso (0 si está libre)
    Nodo* siguiente;
    Nodo* anterior;
    int distancia;

     Nodo(const string& _id, int _distancia); 

    void mostrarEstado() const;
};

#endif // NODO_H
