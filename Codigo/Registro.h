/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#ifndef REGISTRO_H
#define REGISTRO_H

#include "Auto.h"
#include "Propietario.h"

class Registro {
public:
    Auto autoPermitido;
    Propietario propietario;

    Registro(const Auto& autoPermitido, const Propietario& propietario);
    Registro(const Auto& autoPermitido);
    Auto getAutoPermitido() const;
};

#endif // REGISTRO_H
