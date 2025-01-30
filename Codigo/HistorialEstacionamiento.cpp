/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#include "HistorialEstacionamiento.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

HistorialEstacionamiento::HistorialEstacionamiento() {
    cargarDesdeArchivo();
}

string HistorialEstacionamiento::obtenerFechaHoraActual() const {
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buffer);
}

void HistorialEstacionamiento::cargarDesdeArchivo() {
    ifstream archivoEntrada(archivoHistorial);
    if (!archivoEntrada.is_open()) {
        cerr << "No se pudo abrir el archivo " << archivoHistorial << ". Creando uno nuevo." << endl;
        return;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string placa, espacioId, fechaHoraIngreso, fechaHoraSalida;

        getline(ss, placa, ',');
        getline(ss, espacioId, ',');
        getline(ss, fechaHoraIngreso, ',');
        getline(ss, fechaHoraSalida, ',');

        historial.insertar(placa, espacioId, fechaHoraIngreso, fechaHoraSalida);
    }
    archivoEntrada.close();
}

void HistorialEstacionamiento::guardarEnArchivo() {
    ofstream archivoSalida(archivoHistorial, ios::trunc);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo " << archivoHistorial << " para guardar." << endl;
        return;
    }

    vector<NodoRN*> registros = historial.obtenerInOrden();
    for (const auto& registro : registros) {
        archivoSalida << registro->placa << ","
                      << registro->espacioId << ","
                      << registro->fechaHoraIngreso << ","
                      << registro->fechaHoraSalida << "\n";
    }
    archivoSalida.close();
}

void HistorialEstacionamiento::registrarEntrada(const string& placa, const string& espacioId) {
    string fechaHora = obtenerFechaHoraActual();
    historial.insertar(placa, espacioId, fechaHora);
    guardarEnArchivo();
    cout << "Entrada registrada: Placa " << placa << ", Espacio " << espacioId 
         << ", Fecha/Hora: " << fechaHora << endl;
}

bool HistorialEstacionamiento::registrarSalida(const string& placa) {
    NodoRN* nodoEncontrado = nullptr;
    vector<NodoRN*> registros = historial.obtenerInOrden();

    // Buscar la entrada más reciente que aún no tiene salida
    for (const auto& nodo : registros) {
        if (nodo->placa == placa && nodo->fechaHoraSalida.empty()) {
            nodoEncontrado = nodo;
        }
    }

    if (nodoEncontrado != nullptr) {
        nodoEncontrado->fechaHoraSalida = obtenerFechaHoraActual();
        guardarEnArchivo();
        cout << "\nSalida registrada para placa " << nodoEncontrado->placa 
             << " a las " << nodoEncontrado->fechaHoraSalida << "." << endl;
        return true;
    } else {
        cout << "No se encontro una entrada activa para la placa " << placa << "." << endl;
        return false;
    }
}

void HistorialEstacionamiento::mostrarHistorial() const {
    vector<NodoRN*> registros = historial.obtenerInOrden();

    if (registros.empty()) {
        cout << "No hay registros en el historial." << endl;
        return;
    }

    cout << "Historial de Estacionamiento:\n";
    for (const auto& registro : registros) {
        cout << "Placa: " << registro->placa 
             << ", Espacio: " << registro->espacioId 
             << ", Ingreso: " << registro->fechaHoraIngreso 
             << ", Salida: " << (registro->fechaHoraSalida.empty() ? "Aun en el parqueadero" : registro->fechaHoraSalida)
             << endl;
    }
}

string HistorialEstacionamiento::buscarHistorial(const string& placa) const {
    NodoRN* nodo = historial.buscar(placa);

    if (nodo == nullptr) {
        return "No se encontró historial para la placa " + placa;
    }

    string resultado = "Placa: " + nodo->placa 
                     + ", Espacio: " + nodo->espacioId 
                     + ", Ingreso: " + nodo->fechaHoraIngreso 
                     + ", Salida: " + (nodo->fechaHoraSalida.empty() ? "Aun en el parqueadero" : nodo->fechaHoraSalida);
    return resultado;
}

void HistorialEstacionamiento::mostrarHistorialPorFecha(const string& fecha) const {
    vector<NodoRN*> registros = historial.obtenerInOrden();
    bool encontrado = false;

    cout << "Historial de estacionamiento para la fecha: " << fecha << "\n";
    cout << "------------------------------------------------------\n";

    for (const auto& registro : registros) {
        if (registro->fechaHoraIngreso.substr(0, 10) == fecha) {
            cout << "Placa: " << registro->placa 
                 << ", Espacio: " << registro->espacioId 
                 << ", Ingreso: " << registro->fechaHoraIngreso 
                 << ", Salida: " << (registro->fechaHoraSalida.empty() ? "Aun en el parqueadero" : registro->fechaHoraSalida)
                 << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron registros para la fecha: " << fecha << ".\n";
    }
}

void HistorialEstacionamiento::mostrarHistorialPorFechaYPlaca(const string& fecha, const string& placa) const {
    vector<NodoRN*> registros = historial.obtenerInOrden(); // Obtén todos los nodos en orden
    bool encontrado = false; // Para verificar si se encontraron coincidencias

    for (const auto& nodo : registros) {
        // Filtra por placa y fecha
        if (nodo->placa == placa && nodo->fechaHoraIngreso.substr(0, 10) == fecha) {
            encontrado = true;
            cout << "Placa: " << nodo->placa 
                 << ", Espacio: " << nodo->espacioId 
                 << ", Ingreso: " << nodo->fechaHoraIngreso 
                 << ", Salida: " << (nodo->fechaHoraSalida.empty() ? "Aun en el parqueadero" : nodo->fechaHoraSalida)
                 << "\n";
        }
    }

    if (!encontrado) {
        cout << "No se encontraron registros para la placa: " << placa 
             << " en la fecha: " << fecha << ".\n";
    }
}

void HistorialEstacionamiento::mostrarHistorialPorRangoHoras(const string& horaInicio, const string& horaFin) const {
    vector<NodoRN*> registros = historial.obtenerInOrden();
    bool encontrado = false;

    cout << "Historial de estacionamiento para el rango de horas: " << horaInicio << " - " << horaFin << "\n";
    cout << "------------------------------------------------------\n";

    for (const auto& registro : registros) {
        string horaIngreso = registro->fechaHoraIngreso.substr(11, 8); // Extrae solo la hora
        string horaSalida = registro->fechaHoraSalida.empty() ? "" : registro->fechaHoraSalida.substr(11, 8);

        if ((horaIngreso >= horaInicio && horaIngreso <= horaFin) ||
            (!horaSalida.empty() && horaSalida >= horaInicio && horaSalida <= horaFin)) {
            cout << "Placa: " << registro->placa 
                 << ", Espacio: " << registro->espacioId 
                 << ", Ingreso: " << registro->fechaHoraIngreso 
                 << ", Salida: " << (registro->fechaHoraSalida.empty() ? "Aun en el parqueadero" : registro->fechaHoraSalida)
                 << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron registros en el rango de horas especificado." << endl;
    }
}

void HistorialEstacionamiento::mostrarPrimerIngresoPorFecha(const string& fecha) const {
    vector<NodoRN*> registros = historial.obtenerInOrden();
    NodoRN* primerIngreso = nullptr;
    string horaMasTemprana = "23:59:59"; // Inicializamos con una hora alta

    for (const auto& registro : registros) {
        if (registro->fechaHoraIngreso.substr(0, 10) == fecha) {  // Filtra por fecha
            string horaIngreso = registro->fechaHoraIngreso.substr(11, 8); // Extrae HH:MM:SS
            if (!primerIngreso || horaIngreso < horaMasTemprana) { // Compara la hora
                primerIngreso = registro;
                horaMasTemprana = horaIngreso;
            }
        }
    }

    if (!primerIngreso) {
        cout << "No se encontraron registros para la fecha " << fecha << "." << endl;
        return;
    }

    string salida = primerIngreso->fechaHoraSalida.empty() ? "Aun en el parqueadero" : primerIngreso->fechaHoraSalida;

    cout << "Primer ingreso del dia " << fecha << ":\n";
    cout << "Placa: " << primerIngreso->placa
         << ", Espacio: " << primerIngreso->espacioId
         << ", Ingreso: " << primerIngreso->fechaHoraIngreso
         << ", Salida: " << salida << endl;
}

void HistorialEstacionamiento::mostrarAutosPorRangoFechas(const string& fechaInicio, const string& fechaFin) const {
    vector<NodoRN*> registros = historial.obtenerInOrden();
    bool encontrado = false;

    cout << "Autos ingresados entre el " << fechaInicio << " y el " << fechaFin << ":\n";
    cout << "------------------------------------------------------\n";

    for (const auto& registro : registros) {
        string fechaIngreso = registro->fechaHoraIngreso.substr(0, 10);
        if (fechaIngreso >= fechaInicio && fechaIngreso <= fechaFin) {
            string salida = registro->fechaHoraSalida.empty() ? "Aun en el parqueadero" : registro->fechaHoraSalida;

            cout << "Placa: " << registro->placa
                 << ", Espacio: " << registro->espacioId
                 << ", Ingreso: " << registro->fechaHoraIngreso
                 << ", Salida: " << salida << endl;

            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron registros entre las fechas " << fechaInicio << " y " << fechaFin << "." << endl;
    }
}
