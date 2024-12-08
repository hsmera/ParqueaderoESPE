#ifndef MENU_H
#define MENU_H

#include "Parqueadero.h"
#include "AutosPermitidos.h"
#include "HistorialEstacionamiento.h"
#include <vector>
#include <string>
#include <iostream>
#include <conio.h> // Para usar _getch()

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
