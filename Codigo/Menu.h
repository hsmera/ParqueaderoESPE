#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include <conio.h> 
#include "Parqueadero.h"
#include "HistorialEstacionamiento.h"
#include "AutosPermitidos.h"

using namespace std;

class Menu {
private:
    vector<string> opciones;                 // Opciones principales del menú
    int seleccionActual = 0;                 // Índice de la opción seleccionada
    Parqueadero* parqueadero;                // Instancia del parqueadero
    HistorialEstacionamiento* historial;     // Instancia del historial
    AutosPermitidos* autosPermitidos;        // Instancia de los autos permitidos

    void mostrarMenu();                      // Muestra el menú principal
    void ejecutarOpcion();                   // Ejecuta la opción seleccionada
    void mostrarSubmenuAutosPermitidos();    // Submenú para autos permitidos
    void mostrarSubmenuHistorial();          // Submenú para historial de estacionamientos

public:
    Menu(Parqueadero* p, HistorialEstacionamiento* h, AutosPermitidos* a); // Constructor
    void iniciar();                          // Inicia el ciclo del menú
};

#endif 