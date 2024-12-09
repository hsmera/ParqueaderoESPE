/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

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
            placa = validador.ingresarPlaca("Ingresa la placa del auto a estacionar(sin guiones): ");
            cout <<endl;
            if (!autosPermitidos->buscarAuto(placa)) {
                cout << "El auto no esta permitido. Registrelo primero.\n";
                break;
            }
            parqueadero->mostrarEstado();
            espacioId = validador.ingresarEspacioId("Ingrese el id del espacio a estacionarse: ");
            cout<<endl;
            if (parqueadero->estacionarAuto(placa, espacioId)) {
                historial->registrarEntrada(placa, espacioId);
            }
            break;
        }
        case 2: {
            string placa;
            Validaciones<string> validador;
            placa = validador.ingresarPlaca("Ingrese la placa del auto a retirar(sin guiones): ");
            if (parqueadero->retirarAuto(placa)) {
                historial->registrarSalida(placa);
            }
            break;
        }
        case 3: {
            string placa, marca, color, nombre, cedula, correo;
            Validaciones<string> validador;
            placa = validador.ingresarPlaca("Ingrese la placa del auto(sin guiones): ");
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
            placa = validador.ingresarPlaca("Ingrese la placa del auto a eliminar(sin guiones): ");
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
                placa = validador.ingresarPlaca("Ingrese la placa del auto(sin guiones): ");
                cout << endl;

                if (autosPermitidos->buscarAuto(placa)) {
                    autosPermitidos->mostrarAutoPorPlaca(placa); // Mostrar detalles del auto
                } else {
                    cout << "El auto con placa " << placa << " no esta permitido.\n";
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
                placa = validador.ingresarPlaca("Ingrese la placa(sin guiones): ");
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
        } else if (tecla == 59) { // F1 (en ASCII extendido)
            mostrarGuiaRapida();
        }
    }
}

void Menu::mostrarGuiaRapida() {
    system("cls");
    std::cout << "Guia Rapida para el Usuario del Sistema de Parqueadero\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "- Consultar el Estado del Parqueadero\n";
    std::cout << "  Utiliza la opcion 'Mostrar estado del parqueadero' en el menu principal para ver los espacios disponibles y ocupados.\n\n";
    std::cout << "- Estacionar un Auto\n";
    std::cout << "  Asegurate de que el auto este registrado como permitido.\n";
    std::cout << "  Selecciona un espacio disponible.\n\n";
    std::cout << "- Retirar un Auto\n";
    std::cout << "  Ingresa la placa del auto para liberar el espacio ocupado.\n\n";
    std::cout << "- Registrar Autos Permitidos\n";
    std::cout << "  Agrega nuevos autos permitidos ingresando su placa, marca, color y datos del propietario.\n\n";
    std::cout << "- Eliminar Autos Permitidos\n";
    std::cout << "  Elimina autos registrados si no necesitan acceso al parqueadero.\n\n";
    std::cout << "- Visualizar Historial\n";
    std::cout << "  Consulta las entradas y salidas del parqueadero por placa o fecha.\n\n";
    std::cout << "- Navegacion del Menu\n";
    std::cout << "  Usa las flechas del teclado para moverte entre las opciones.\n";
    std::cout << "  El sistema actualizara automaticamente la informacion despues de cada operacion.\n\n";
    std::cout << "Presiona cualquier tecla para regresar al menu principal...\n";
    _getch(); // Esperar a que el usuario presione una tecla
}
