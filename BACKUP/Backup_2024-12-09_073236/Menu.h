/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#ifndef MENU_H
#define MENU_H

#include "Parqueadero.h"
#include "AutosPermitidos.h"
#include "HistorialEstacionamiento.h"
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>

class Menu {
private:
    Parqueadero* parqueadero;
    HistorialEstacionamiento* historial;
    AutosPermitidos* autosPermitidos;

    vector<string> opciones;
    int seleccionActual;

    void mostrarSubmenuAutosPermitidos();
    void mostrarSubmenuHistorial();

public:
    Menu(Parqueadero* p, HistorialEstacionamiento* h, AutosPermitidos* a);
    void mostrarMenu();
    void ejecutarOpcion();
    void iniciar();
};

#endif // MENU_H