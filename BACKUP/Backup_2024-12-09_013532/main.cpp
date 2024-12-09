#include "Menu.h"

int main() {
    Parqueadero parqueadero;
    HistorialEstacionamiento historial;
    AutosPermitidos autosPermitidos;

    Menu menu(&parqueadero, &historial, &autosPermitidos);
    menu.iniciar();

    return 0;
}
