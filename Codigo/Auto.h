/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#ifndef AUTO_H
#define AUTO_H

#include <string>
using namespace std;

class Auto {
public:
    string placa;
    string marca;
    string color;

    Auto(const string& placa, const string& marca, const string& color);
};

#endif // AUTO_H
