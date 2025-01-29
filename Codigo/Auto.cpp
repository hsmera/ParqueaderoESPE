/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#include "Auto.h"

Auto::Auto(const string& placa, const string& marca, const string& color)
    : placa(placa), marca(marca), color(color) {}

std::string Auto::getPlaca() const {
    return placa; // Retorna la placa del auto
}

std::string Auto::getMarca() const {
    return marca;
}

std::string Auto::getColor() const {
    return color;
}