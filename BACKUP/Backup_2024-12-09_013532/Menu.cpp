#include "Menu.h"
#include "Validaciones.h"
#include <iostream>
#include "HistorialEstacionamiento.h"
using namespace std;
// Constructor: Inicializa el menú con las opciones disponibles
Menu::Menu(Parqueadero* p, HistorialEstacionamiento* h, AutosPermitidos* a)
    : parqueadero(p), historial(h), autosPermitidos(a), seleccionActual(0) {
    opciones = {
        "Mostrar estado del parqueadero",
        "Estacionar un auto",
        "Retirar un auto",
        "Registrar auto permitido",
        "Eliminar auto permitido",
        "Mostrar autos permitidos",
        "Mostrar propietarios",
        "Mostrar historial de estacionamientos",
        "Salir"
    };
}

// Mostrar el menú principal
void Menu::mostrarMenu() {
    system("cls");
    cout << "Sistema de Gestion de Parqueadero\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < opciones.size(); i++) {
        if (i == seleccionActual) {
            cout << " > " << opciones[i] << " <\n"; // Opción seleccionada
        } else {
            cout << "   " << opciones[i] << "\n"; // Opción no seleccionada
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
            string placa, espacioId;
            Validaciones<string> validador;
            Validaciones<int> ingresar_Entero;
            placa = validador.ingresarPlaca("Ingresa la placa del auto a estacionar: ");
            cout <<endl;
            if (!autosPermitidos->buscarAuto(placa)) {
                cout << "El auto no esta permitido. Registrelo primero.\n";
                break;
            }
            parqueadero->mostrarEstado();
            cout<<"Ingrese el id del espacio a estacionarse: ";
            cin>>espacioId;
            if (parqueadero->estacionarAuto(placa, espacioId)) {
                historial->registrarEntrada(placa, espacioId);
            }
            break;
        }
        case 2: {
            string placa;
            Validaciones<string> validador;
            placa = validador.ingresarPlaca("Ingrese la placa del auto a retirar: ");
            if (parqueadero->retirarAuto(placa)) {
                historial->registrarSalida(placa);
            }
            break;
        }
        case 3: {
            string placa, marca, color, nombre, cedula, correo;
            Validaciones<string> validador;
            placa = validador.ingresarPlaca("Ingrese la placa del auto: ");
            cout <<endl;
            marca = validador.ingresar("Ingrese la marca del auto: ", "string");
            cout<<endl;
            color = validador.ingresar("Ingrese el color: ","string");
            cout<<endl;
            nombre = validador.ingresar("Ingrese el nombre del propietario: ","string");
            cout<<endl;
            cedula = validador.ingresarCedula("Ingrese la cedula del propietario: ");
            cout<<endl;
            correo = validador.ingresarCorreo("Ingrese el correo del propietario: ");
            cout<<endl;
            Auto autoObj(placa, marca, color);
            Propietario propietario(nombre, cedula, correo);
            autosPermitidos->agregarAuto(autoObj, propietario);
            break;
        }
        case 4: {
            string placa;
            Validaciones<string> validador;
            placa = validador.ingresarPlaca("Ingrese la placa del auto a eliminar: ");
            cout<<endl;
            autosPermitidos->eliminarAuto(placa);
            break;
        }
        case 5:
            mostrarSubmenuAutosPermitidos();
            break;
        case 6:
            autosPermitidos->mostrarPropietarios();
            break;
        case 7:
            mostrarSubmenuHistorial();
            break;
        case 8:
            cout << "Saliendo del programa...\n";
            exit(0);
        default:
            cout << "Opcion no valida.\n";
            break;
    }
    system("pause");
}

// Mostrar submenú de autos permitidos
void Menu::mostrarSubmenuAutosPermitidos() {
    vector<string> opcionesAutos = {
        "Mostrar todos los autos permitidos",
        "Buscar auto por placa",
        "Regresar al menu principal"
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
        if (tecla == 72) { // Flecha arriba
            seleccionSubmenu = (seleccionSubmenu - 1 + opcionesAutos.size()) % opcionesAutos.size();
        } else if (tecla == 80) { // Flecha abajo
            seleccionSubmenu = (seleccionSubmenu + 1) % opcionesAutos.size();
        } else if (tecla == '\r') { // Enter
            system("cls");
            if (seleccionSubmenu == 0) { 
                // Opción: Mostrar todos los autos permitidos
                autosPermitidos->mostrarAutos();
            } else if (seleccionSubmenu == 1) { 
                // Opción: Buscar auto por placa
                string placa;
                Validaciones<string> validador;
                placa = validador.ingresarPlaca("Ingrese la placa del auto: ");
                cout << endl;

                if (autosPermitidos->buscarAuto(placa)) {
                    autosPermitidos->mostrarAutoPorPlaca(placa); // Mostrar detalles del auto
                } else {
                    cout << "El auto con placa " << placa << " no está permitido.\n";
                }
            } else if (seleccionSubmenu == 2) { 
                // Opción: Regresar al menú principal
                break;
            }
            system("pause");
        }
    }
}

// Mostrar submenú del historial
void Menu::mostrarSubmenuHistorial() {
    vector<string> opcionesHistorial = {
        "Mostrar historial por fecha",
        "Mostrar historial por fecha y placa",
        "Regresar al menu principal"
    };
    int seleccionSubmenu = 0;

    while (true) {
        system("cls");
        cout << "Opciones de Historial\n";
        cout << "-----------------------\n";

        for (int i = 0; i < opcionesHistorial.size(); i++) {
            if (i == seleccionSubmenu) {
                cout << " > " << opcionesHistorial[i] << " <\n";
            } else {
                cout << "   " << opcionesHistorial[i] << "\n";
            }
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha arriba
            seleccionSubmenu = (seleccionSubmenu - 1 + opcionesHistorial.size()) % opcionesHistorial.size();
        } else if (tecla == 80) { // Flecha abajo
            seleccionSubmenu = (seleccionSubmenu + 1) % opcionesHistorial.size();
        } else if (tecla == '\r') { // Enter
            system("cls");
            if (seleccionSubmenu == 0) {
                string fecha;
                Validaciones<string> validador;
                fecha = validador.ingresarFecha("Ingrese la fecha (YYYY-MM-DD): ");
                cout<<endl;
                historial->mostrarHistorialPorFecha(fecha);
                cout<<endl;
            } else if (seleccionSubmenu == 1) {
                string fecha, placa;
                Validaciones<string> validador;
                fecha = validador.ingresarFecha("Ingrese la fecha (YYYY-MM-DD): ");
                cout<<endl;
                placa = validador.ingresarPlaca("Ingrese la placa: ");
                cout<<endl;
                historial->mostrarHistorialPorFechaYPlaca(fecha, placa);
            } else if (seleccionSubmenu == 2) {
                break; // Regresar al menú principal
            }
            system("pause");
        }
    }
}

// Iniciar el menú interactivo
void Menu::iniciar() {
    while (true) {
        mostrarMenu();
        char tecla = _getch();
        if (tecla == 72) { // Flecha arriba
            seleccionActual = (seleccionActual - 1 + opciones.size()) % opciones.size();
        } else if (tecla == 80) { // Flecha abajo
            seleccionActual = (seleccionActual + 1) % opciones.size();
        } else if (tecla == '\r') { // Enter
            ejecutarOpcion();
        }
    }
}
