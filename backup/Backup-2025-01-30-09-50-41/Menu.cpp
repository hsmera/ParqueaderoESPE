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
#include "Ordenamientos.h"
#include <conio.h>
#include <algorithm>
#include <functional>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include "BusquedaBinaria.h"
#include "Backup.h"


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
        "Opciones de Busqueda",
        "Ordenar autos permitidos",
        "Mostrar propietarios",
        "Mostrar historial de estacionamientos",
        "Opciones de Backup",
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
            if (parqueadero->retirarAuto(placa)){
                historial->registrarSalida(placa);
            }
            break;
        }
        case 5:
            autosPermitidos->mostrarAutos();
            break;
        case 6:
            submenuBusquedas();
            break;
        case 7: // Agregar caso para ordenar los autos permitidos
            mostrarMenuOrdenamiento(autosPermitidos->getRegistros());
            break;
        case 8:
            autosPermitidos->mostrarPropietarios();
            break;
        case 9:
            mostrarSubmenuHistorial();
            break;
        case 10:
            Backup backup;
            mostrarSubmenuBackup(backup);
            break;
        case 11:
            cout << "Saliendo del programa...\n";
            exit(0);
        default:
            cout << "Opcion no valida.\n";
            break;
    }
    system("pause");
}

void Menu::mostrarSubmenuBackup(Backup& backup) {
    vector<string> opcionesBackup = {
        "Realizar Backup de todos los archivos",
        "Realizar Backup de un archivo especifico",
        "Eliminar un archivo",
        "Recuperar un Backup",
        "Regresar al menu principal"
    };

    int seleccionSubmenu = 0;

    while (true) {
        system("cls");
        cout << "\nOpciones de Backup\n";
        cout << "-----------------------\n";
        
        for (int i = 0; i < opcionesBackup.size(); i++) {
            if (i == seleccionSubmenu) {
                cout << " > " << opcionesBackup[i] << " <\n";
            } else {
                cout << "   " << opcionesBackup[i] << "\n";
            }
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha arriba
            seleccionSubmenu = (seleccionSubmenu - 1 + opcionesBackup.size()) % opcionesBackup.size();
        } else if (tecla == 80) { // Flecha abajo
            seleccionSubmenu = (seleccionSubmenu + 1) % opcionesBackup.size();
        } else if (tecla == '\r') { // Enter
            system("cls");
            if (seleccionSubmenu == 0) {
                backup.realizarBackupTodos();
            } else if (seleccionSubmenu == 1) {
                backup.realizarBackupEspecifico();
            } else if (seleccionSubmenu == 2) {
                backup.eliminarArchivo();
            } else if (seleccionSubmenu == 3) {
                backup.recuperarBackup();
            } else if (seleccionSubmenu == 4) {
                break; // Regresar al menú principal
            }
            system("pause");
        }
    }
}

// Mostrar submenú de autos permitidos
void Menu::submenuBusquedas()
{
    vector<string> opcionesAutos = {
        "Buscar auto por placa",
        "Buscar autos permitidos por prefijo de placa",  // Opción nueva
        "Buscar el primer ingreso por fecha especifica", // Opción nueva
        "Buscar autos por rango de fechas",  // Opción nueva
        "Regresar al menu principal"};

    int seleccionSubmenu = 0;

    while (true)
    {
        system("cls");
        cout << "   Opciones de Busqueda      \n";
        cout << "-----------------------------\n";

        for (int i = 0; i < opcionesAutos.size(); i++)
        {
            if (i == seleccionSubmenu)
            {
                cout << " > " << opcionesAutos[i] << " <\n";
            }
            else
            {
                cout << "   " << opcionesAutos[i] << "\n";
            }
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha arriba
            seleccionSubmenu = (seleccionSubmenu - 1 + opcionesAutos.size()) % opcionesAutos.size();
        }
        else if (tecla == 80)
        { // Flecha abajo
            seleccionSubmenu = (seleccionSubmenu + 1) % opcionesAutos.size();
        }
        else if (tecla == '\r')
        { // Enter
            system("cls");
            if (seleccionSubmenu == 0)
            {
                // Opción: Buscar auto por placa
                string placa;
                Validaciones<string> validador;
                placa = validador.ingresarPlaca("Ingrese la placa del auto(sin guiones): ");
                cout << endl;

                if (autosPermitidos->buscarAuto(placa))
                {
                    autosPermitidos->mostrarAutoPorPlaca(placa); // Mostrar detalles del auto
                }
                else
                {
                    cout << "El auto con placa " << placa << " no está permitido.\n";
                }
            }
            else if (seleccionSubmenu == 1)
            {
                // Opción: Buscar autos por prefijo de placa
                string prefijo;
                Validaciones<string> validador;
                prefijo = validador.ingresarPrefijo("Ingrese el prefijo de la placa(Ejem: XYZ): ");
                cout<<endl;
                // Usar la clase BusquedaBinaria para encontrar los autos con el prefijo
                BusquedaBinaria::mostrarRegistros(autosPermitidos->getRegistros(), prefijo);
            }
            else if (seleccionSubmenu == 2)
            {
                // Opción: Buscar el primer ingreso por fecha específica
                string fecha;
                Validaciones<string> validador;
                fecha = validador.ingresarFecha("Ingrese la fecha de busqueda (YYYY-MM-DD): ");
                cout << endl;

                // Llamar al método de HistorialEstacionamiento para mostrar el primer ingreso
                historial->mostrarPrimerIngresoPorFecha(fecha);
            }
            else if (seleccionSubmenu == 3)
            {
                // Opción: Buscar autos por rango de fechas
                string fechaInicio, fechaFin;
                Validaciones<string> validador;
                fechaInicio = validador.ingresarFecha("Ingrese la fecha de inicio (YYYY-MM-DD): ");
                cout <<endl;
                fechaFin = validador.ingresarFecha("Ingrese la fecha de fin (YYYY-MM-DD): ");
                cout << endl;

                // Llamar al método de HistorialEstacionamiento para mostrar autos en el rango de fechas
                historial->mostrarAutosPorRangoFechas(fechaInicio, fechaFin);
            }
            else if (seleccionSubmenu == 4)
            {
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
        "Mostrar historial por rango de hora",
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
                cout << endl;
                historial->mostrarHistorialPorFecha(fecha);
                cout << endl;
            } else if (seleccionSubmenu == 1) {
                string fecha, placa;
                Validaciones<string> validador;
                fecha = validador.ingresarFecha("Ingrese la fecha (YYYY-MM-DD): ");
                cout << endl;
                placa = validador.ingresarPlaca("Ingrese la placa (sin guiones): ");
                cout << endl;
                historial->mostrarHistorialPorFechaYPlaca(fecha, placa);
            } else if (seleccionSubmenu == 2) {
                string horaInicio, horaFin;
                Validaciones<string> validador;
                horaInicio = validador.ingresarHora("Ingrese la hora de inicio (HH:MM:SS): ");
                cout << endl;
                horaFin = validador.ingresarHora("Ingrese la hora de fin (HH:MM:SS): ");
                cout << endl;
                historial->mostrarHistorialPorRangoHoras(horaInicio, horaFin);
                cout << endl;
            } else if (seleccionSubmenu == 3) {
                break; // Regresar al menú principal
            }
            system("pause");
        }
    }
}

void Menu::mostrarMenuOrdenamiento(std::list<Registro> &registros) // Modificado
{
    std::vector<std::string> opcionesOrdenamiento = {
        "Shell Sort",
        "Bubble Sort",
        "Quick Sort",
        "Radix Sort",
        "Bucket Sort",
        "Heap Sort",
        "Salir"};
    int seleccionMenu = 0;

    while (true)
    {
        system("cls");
        std::cout << "Opciones de Ordenamiento\n";
        std::cout << "--------------------------\n";

        for (int i = 0; i < opcionesOrdenamiento.size(); i++)
        {
            if (i == seleccionMenu)
            {
                std::cout << " > " << opcionesOrdenamiento[i] << " <\n";
            }
            else
            {
                std::cout << "   " << opcionesOrdenamiento[i] << "\n";
            }
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha arriba
            seleccionMenu = (seleccionMenu - 1 + opcionesOrdenamiento.size()) % opcionesOrdenamiento.size();
        }
        else if (tecla == 80)
        { // Flecha abajo
            seleccionMenu = (seleccionMenu + 1) % opcionesOrdenamiento.size();
        }
        else if (tecla == '\r')
        { // Enter
            system("cls");
            if (seleccionMenu == 0)
            {
                std::cout << "Ejecutando Shell Sort...\n";
                // Usando un comparador (por ejemplo, por placa en orden ascendente)
                Ordenamientos::shellSort(registros, [](const Auto &a, const Auto &b)
                                         { return a.placa < b.placa; });
                Ordenamientos::guardarEnArchivo(registros, "autos_ordenados_ShellSort.txt");
            }
            else if (seleccionMenu == 1)
            {
                std::cout << "Ejecutando Bubble Sort...\n";
                Ordenamientos::bubbleSort(registros, [](const Auto &a, const Auto &b)
                                          { return a.placa < b.placa; });
                Ordenamientos::guardarEnArchivo(registros, "autos_ordenados_BubbleSort.txt");
            }
            else if (seleccionMenu == 2)
            {
                std::cout << "Ejecutando Quick Sort...\n";
                // Usando un comparador (por ejemplo, por placa en orden ascendente)
                Ordenamientos::quickSort(registros, [](const Auto &a, const Auto &b)
                                         { return a.placa < b.placa; });
                Ordenamientos::guardarEnArchivo(registros, "autos_ordenados_QuickSort.txt");
            }
            else if (seleccionMenu == 3)
            {
                std::cout << "Ejecutando Radix Sort...\n";
                Ordenamientos::radixSort(registros, [](const Auto &a, const Auto &b)
                                         { return a.placa < b.placa; });
                Ordenamientos::guardarEnArchivo(registros, "autos_ordenados_RadixSort.txt");
            }
            else if (seleccionMenu == 4)
            {
                std::cout << "Ejecutando Bucket Sort...\n";
                Ordenamientos::bucketSort(registros, [](const Auto &a, const Auto &b)
                                          { return a.placa < b.placa; });
                Ordenamientos::guardarEnArchivo(registros, "autos_ordenados_BucketSort.txt");
            }
            else if (seleccionMenu == 5)
            {
                std::cout << "Ejecutando Heap Sort...\n";
                Ordenamientos::heapSort(registros, [](const Auto &a, const Auto &b)
                                        { return a.placa < b.placa; });
                Ordenamientos::guardarEnArchivo(registros, "autos_ordenados_HeapSort.txt");
            }
            else if (seleccionMenu == 6)
            {
                break; // Salir del menú
            }
            std::cout << "Ordenamiento completado.\n";
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

void Menu::ordenarAutosPermitidos() {
    // Llamamos al método de ordenar de la clase AutosPermitidos
    autosPermitidos->ordenarAutos();  // Suponiendo que 'ordenarAutos' está implementado en AutosPermitidos
    cout << "Autos permitidos ordenados correctamente." << endl;
}

