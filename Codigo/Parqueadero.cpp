#include "Parqueadero.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Constructor: Inicializa la lista circular y carga los datos
Parqueadero::Parqueadero() {
    EspacioParqueadero gestorEspacios;

    // Verificar si el archivo de estado existe y tiene datos válidos
    ifstream file(archivoParqueadero);
    if (file.is_open() && file.peek() != ifstream::traits_type::eof()) {
        // Cargar datos desde el archivo
        espacios = gestorEspacios.crearListaCircular(capacidad);
        cargarDatos();
    } else {
        // Si no hay datos, crear una nueva lista circular
        espacios = gestorEspacios.crearListaCircular(capacidad);
        guardarDatos(); // Guardar el estado inicial (vacío)
    }
    file.close();
}

// Método para cargar datos desde el archivo
void Parqueadero::cargarDatos() {
    ifstream file(archivoParqueadero);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << archivoParqueadero << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string id, placa, marca, color, nombre, cedula, correo, fechaIngreso, fechaSalida;
        bool ocupado;

        getline(ss, id, ',');
        getline(ss, placa, ',');
        getline(ss, marca, ',');
        getline(ss, color, ',');
        getline(ss, nombre, ',');
        getline(ss, cedula, ',');
        getline(ss, correo, ',');
        getline(ss, fechaIngreso, ',');
        getline(ss, fechaSalida, ',');

        Nodo* espacio = EspacioParqueadero().buscarEspacio(id, espacios);
        if (espacio) {
            espacio->ocupado = !placa.empty(); // Determina si está ocupado
            espacio->placa = placa;
            espacio->marca = marca;
            espacio->color = color;
            espacio->nombrePropietario = nombre;
            espacio->cedula = cedula;
            espacio->correo = correo;
            espacio->fechaHoraIngreso = fechaIngreso;
            espacio->fechaHoraSalida = fechaSalida;
        }
    }

    file.close();
}

// Método para guardar el estado actual en el archivo
void Parqueadero::guardarDatos() {
    ofstream file(archivoParqueadero, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para guardar datos.\n";
        return;
    }

    Nodo* actual = espacios;
    do {
        file << actual->id << ","
             << actual->placa << ","
             << actual->marca << ","
             << actual->color << ","
             << actual->nombrePropietario << ","
             << actual->cedula << ","
             << actual->correo << ","
             << actual->fechaHoraIngreso << "-"
             << actual->fechaHoraSalida << "\n";
        actual = actual->siguiente;
    } while (actual != espacios);

    file.close();
}

// Obtener datos completos por placa desde archivo externo
pair<Auto, Propietario> Parqueadero::obtenerDatosPorPlaca(const string& placa) {
    ifstream file("Autos_permitidos.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo Autos_permitidos.txt\n";
        throw runtime_error("Error al abrir archivo de autos permitidos");
    }

    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string p, marca, color, nombre, cedula, correo;

        getline(ss, p, ',');
        getline(ss, marca, ',');
        getline(ss, color, ',');
        getline(ss, nombre, ',');
        getline(ss, cedula, ',');
        getline(ss, correo, ',');

        if (p == placa) {
            file.close();
            Auto autoObj(p, marca, color);
            Propietario propietario(nombre, cedula, correo);
            return make_pair(autoObj, propietario);
        }
    }

    file.close();
    throw runtime_error("Placa no encontrada en Autos_permitidos.txt");
}

// Obtener la fecha y hora actual en formato legible
string Parqueadero::obtenerFechaHoraActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(ahora);
    tm localTime = *localtime(&tiempo);
    stringstream ss;
    ss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Estacionar un auto en un espacio específico
void Parqueadero::estacionarAuto(const Auto& autoObj, const Propietario& propietario, const string& espacioId) {
    Nodo* espacio = EspacioParqueadero().buscarEspacio(espacioId, espacios);
    if (!espacio) {
        cout << "Error: Espacio no encontrado.\n";
        return;
    }

    if (espacio->ocupado) {
        cout << "Error: El espacio " << espacioId << " ya está ocupado.\n";
        return;
    }

    try {
        auto datos = obtenerDatosPorPlaca(autoObj.getPlaca());
        const Auto& autoCompleto = datos.first;
        const Propietario& propietarioCompleto = datos.second;

        EspacioParqueadero().ocuparEspacio(espacio, autoCompleto.getPlaca(), espacios);
        espacio->marca = autoCompleto.getMarca();
        espacio->color = autoCompleto.getColor();
        espacio->nombrePropietario = propietarioCompleto.getNombre();
        espacio->cedula = propietarioCompleto.getCedula();
        espacio->correo = propietarioCompleto.getCorreo();
        espacio->fechaHoraIngreso = obtenerFechaHoraActual();

        guardarDatos();
        cout << "Auto estacionado correctamente en el espacio " << espacioId << endl;
    } catch (const exception& e) {
        cerr << "Error al estacionar el auto: " << e.what() << endl;
    }
}

// Retirar un auto por placa
void Parqueadero::retirarAuto(const string& placa) {
    Nodo* actual = espacios;
    do {
        if (actual->ocupado && actual->placa == placa) {
            actual->fechaHoraSalida = obtenerFechaHoraActual();
            EspacioParqueadero().liberarEspacio(actual);
            guardarDatos();
            cout << "Auto retirado del espacio " << actual->id << endl;
            return;
        }
        actual = actual->siguiente;
    } while (actual != espacios);

    cout << "Error: No se encontró un auto con la placa " << placa << ".\n";
}

// Mostrar el estado actual del parqueadero
void Parqueadero::mostrarEstado() {
    Nodo* actual = espacios;
    cout << "\nEstado del Parqueadero:\n";
    do {
        cout << "[" << actual->id << "] " << (actual->ocupado ? "Ocupado" : "Libre") << endl;
        actual = actual->siguiente;
    } while (actual != espacios);
}