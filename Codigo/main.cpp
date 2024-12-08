#include "Menu.h"
#include "Parqueadero.h"
#include "HistorialEstacionamiento.h"
#include "AutosPermitidos.h"

int main() {
    // Crear instancias principales
    Parqueadero parqueadero;
    HistorialEstacionamiento historial;
    AutosPermitidos autosPermitidos;

    // Crear el menú
    Menu menu(&parqueadero, &historial, &autosPermitidos);

    // Iniciar el programa
    menu.iniciar();

    return 0;
}

