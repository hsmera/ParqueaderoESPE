#include "Menu.h"

// Constructor
Menu::Menu(Parqueadero* p, HistorialEstacionamiento* h, AutosPermitidos* a)
    : parqueadero(p), historial(h), autosPermitidos(a) {
    // Inicializamos las opciones del menú.
    opciones = {
        "Mostrar estado del parqueadero",
        "Estacionar un auto",
        "Retirar un auto",
        "Registrar auto permitido",
        "Eliminar auto permitido",
        "Mostrar autos permitidos",
        "Mostrar historial de estacionamientos",
        "Salir"
    };
}

// Mostrar menú principal
void Menu::mostrarMenu() {
    system("cls");
    cout << "Sistema de Gestion de Parqueadero\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < opciones.size(); i++) {
        if (i == seleccionActual) {
            cout << " > " << opciones[i] << " <\n"; // Opción seleccionada.
        } else {
            cout << "   " << opciones[i] << "\n"; // Opción no seleccionada.
        }
    }
}

// Ejecutar la opción seleccionada
void Menu::ejecutarOpcion() {
    system("cls");
    switch (seleccionActual) {
        case 0:
            parqueadero->mostrarEstado();
            break;
        case 1: {
            string placa, marca, color, espacioId, nombre, cedula, correo;
            cout << "Ingrese la placa del auto: ";
            cin >> placa;
            if (!autosPermitidos->buscarAuto(placa)) {
                cout << "El auto no está permitido. Regístrelo primero.\n";
                break;
            }
            parqueadero->mostrarEstado();
            cout << "\nIngrese el ID del espacio a ocupar: ";
            cin >> espacioId;
            Auto autoObj(placa, marca, color);
            Propietario propietario(nombre, cedula, correo);
            parqueadero->estacionarAuto(autoObj, propietario, espacioId);
            break;
        }
        case 2: {
            string placa;
            cout << "Ingrese la placa del auto: ";
            cin >> placa;
            parqueadero->retirarAuto(placa);
            break;
        }
        case 3: {
            string placa, marca, color, nombre, cedula, correo;
            cout << "Ingrese la placa del auto: ";
            cin >> placa;
            cout << "Ingrese la marca del auto: ";
            cin >> marca;
            cout << "Ingrese el color del auto: ";
            cin >> color;
            cout << "Ingrese el nombre del propietario: ";
            cin >> nombre;
            cout << "Ingrese la cedula del propietario: ";
            cin >> cedula;
            cout << "Ingrese el correo del propietario: ";
            cin >> correo;
            Auto autoObj(placa, marca, color);
            Propietario propietario(nombre, cedula, correo);
            autosPermitidos->agregarAuto(autoObj, propietario);
            break;
        }
        case 4: {
            string placa;
            cout << "Ingrese la placa del auto a eliminar: ";
            cin >> placa;
            autosPermitidos->eliminarAuto(placa);
            break;
        }
        case 5:
            mostrarSubmenuAutosPermitidos();
            break;
        case 6:
            mostrarSubmenuHistorial();
            break;
        case 7:
            cout << "Saliendo del programa...\n";
            exit(0);
        default:
            cout << "Opción no válida.\n";
            break;
    }
    system("pause");
}

// Mostrar el submenú de autos permitidos
void Menu::mostrarSubmenuAutosPermitidos() {
    vector<string> opcionesAutos = {
        "Mostrar todos los autos permitidos",
        "Buscar auto por placa"
    };
    int seleccionSubmenu = 0;

    while (true) {
        system("cls");
        cout << "Opciones de Autos Permitidos\n";
        cout << "-----------------------------\n";

        for (int i = 0; i < opcionesAutos.size(); i++) {
            if (i == seleccionSubmenu) {
                cout << " > " << opcionesAutos[i] << " <\n";
            } else {
                cout << "   " << opcionesAutos[i] << "\n";
            }
        }

        char tecla = _getch();
        if (tecla == 72) {
            seleccionSubmenu = (seleccionSubmenu - 1 + opcionesAutos.size()) % opcionesAutos.size();
        } else if (tecla == 80) {
            seleccionSubmenu = (seleccionSubmenu + 1) % opcionesAutos.size();
        } else if (tecla == '\r') {
            system("cls");
            if (seleccionSubmenu == 0) {
                autosPermitidos->mostrarAutos();
            } else if (seleccionSubmenu == 1) {
                string placa;
                cout << "Ingrese la placa del auto: ";
                cin >> placa;
                if (!autosPermitidos->buscarAuto(placa)) {
                    cout << "El auto con placa " << placa << " no está permitido.\n";
                }
            }
            system("pause");
            break;
        }
    }
}

// Mostrar el submenú del historial
void Menu::mostrarSubmenuHistorial() {
    vector<string> opcionesHistorial = {
        "Mostrar historial completo",
        "Mostrar historial por placa"
    };
    int seleccionSubmenu = 0;

    while (true) {
        system("cls");
        cout << "Opciones de Historial de Estacionamiento\n";
        cout << "----------------------------------------\n";

        for (int i = 0; i < opcionesHistorial.size(); i++) {
            if (i == seleccionSubmenu) {
                cout << " > " << opcionesHistorial[i] << " <\n";
            } else {
                cout << "   " << opcionesHistorial[i] << "\n";
            }
        }

        char tecla = _getch();
        if (tecla == 72) {
            seleccionSubmenu = (seleccionSubmenu - 1 + opcionesHistorial.size()) % opcionesHistorial.size();
        } else if (tecla == 80) {
            seleccionSubmenu = (seleccionSubmenu + 1) % opcionesHistorial.size();
        } else if (tecla == '\r') {
            system("cls");
            if (seleccionSubmenu == 0) {
                historial->mostrarHistorialCompleto();
            } else if (seleccionSubmenu == 1) {
                string placa;
                cout << "Ingrese la placa del auto: ";
                cin >> placa;
                cout << historial->obtenerHistorialPorPlaca(placa) << endl;
            }
            system("pause");
            break;
        }
    }
}

// Inicia el ciclo del menú
void Menu::iniciar() {
    while (true) {
        mostrarMenu();
        char tecla = _getch();
        if (tecla == 72) {
            seleccionActual = (seleccionActual - 1 + opciones.size()) % opciones.size();
        } else if (tecla == 80) {
            seleccionActual = (seleccionActual + 1) % opciones.size();
        } else if (tecla == '\r') {
            ejecutarOpcion();
        }
    }
}

