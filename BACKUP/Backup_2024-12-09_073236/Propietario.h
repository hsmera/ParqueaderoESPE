/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <string>
using namespace std;

class Propietario {
public:
    string nombre;
    string cedula;
    string correo;

    Propietario(const string& nombre, const string& cedula, const string& correo);
};

#endif // PROPIETARIO_H
