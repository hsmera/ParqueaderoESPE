#include "Parqueadero.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>

// Constructor: Inicializa la lista circular y carga los datos
Parqueadero::Parqueadero() {
    EspacioParqueadero gestorEspacios;
    
    // Verificar si el archivo de estado existe y tiene datos
    ifstream file(archivoParqueadero);
    if (file.is_open() && file.peek() != ifstream::traits_type::eof()) {
        espacios = gestorEspacios.crearListaCircular(capacidad);
        cargarDatos(); // Cargar el estado desde el archivo
    } else {
        // Si no hay datos, crear una nueva lista circular
        espacios = gestorEspacios.crearListaCircular(capacidad);
        guardarDatos(); // Guardar el estado inicial (vacío)
    }
    file.close();
}

// Cargar datos desde archivos
void Parqueadero::cargarDatos() {
    ifstream file(archivoParqueadero);
    if (file.is_open()) {
        string linea;
        while (getline(file, linea)) {
            size_t delimPos = linea.find(',');
            string id = linea.substr(0, delimPos);
            bool ocupado = (linea.substr(delimPos + 1) == "1");

            Nodo* espacio = EspacioParqueadero().buscarEspacio(id, espacios);
            if (espacio) {
                espacio->ocupado = ocupado;
                espacio->placa = ocupado ? espacio->placa : ""; // Limpia la placa si está libre
            }
        }
        file.close();
    }
}

// Guardar estado en archivos
void Parqueadero::guardarDatos() {
    ofstream file(archivoParqueadero, ios::trunc);
    Nodo* actual = espacios;
    if (file.is_open()) {
        do {
            file << actual->id << "," << (actual->ocupado ? "1" : "0") << endl;
            actual = actual->siguiente;
        } while (actual != espacios);
        file.close();
    }
}

string obtenerFechaHoraActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(ahora);
    tm localTime = *localtime(&tiempo);
    stringstream ss;
    ss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

pair<Auto, Propietario> obtenerDatosPorPlaca(const string& placa) {
    ifstream file("Autos_permitidos.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo Autos_permitidos.txt" << endl;
        throw runtime_error("Error al abrir archivo de autos permitidos");
    }

    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string p, marca, color, nombre, cedula, correo;

        // Descomponer línea en campos
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

// Modificar estacionarAuto para guardar más datos
void Parqueadero::estacionarAuto(const Auto& autoObj, const Propietario& propietario, const string& espacioId) {
    Nodo* espacio = EspacioParqueadero().buscarEspacio(espacioId, espacios);
    if (espacio && !espacio->ocupado) {
        try {
            // Obtener datos completos desde Autos_permitidos.txt
            auto datos = obtenerDatosPorPlaca(autoObj.getPlaca());
            const Auto& autoCompleto = datos.first;
            const Propietario& propietarioCompleto = datos.second;

            // Registrar datos en el nodo
            EspacioParqueadero().ocuparEspacio(espacio, autoCompleto.getPlaca());
            espacio->marca = autoCompleto.getMarca();
            espacio->color = autoCompleto.getColor();
            espacio->nombrePropietario = propietarioCompleto.getNombre();
            espacio->cedula = propietarioCompleto.getCedula();
            espacio->correo = propietarioCompleto.getCorreo();
            espacio->fechaHoraIngreso = obtenerFechaHoraActual();

            // Guardar en archivo
            ofstream file(archivoEspacio, ios::app);
            if (file.is_open()) {
                file << espacio->id << "," 
                     << espacio->placa << ","
                     << espacio->marca << ","
                     << espacio->color << ","
                     << espacio->nombrePropietario << ","
                     << espacio->cedula << ","
                     << espacio->correo << ","
                     << espacio->fechaHoraIngreso << ",\n";
                file.close();
            }

            guardarDatos();
            cout << "Auto estacionado correctamente en el espacio " << espacioId << endl;
        } catch (const exception& e) {
            cerr << "Error al estacionar el auto: " << e.what() << endl;
        }
    } else {
        cout << "Espacio no disponible o ya ocupado.\n";
    }
}

void Parqueadero::retirarAuto(const string& placa) {
    Nodo* actual = espacios;
    do {
        if (actual->placa == placa) {
            // Registrar salida
            actual->fechaHoraSalida = obtenerFechaHoraActual();
            
            // Actualizar archivo
            fstream file(archivoEspacio, ios::in | ios::out);
            string linea, nuevoContenido;
            while (getline(file, linea)) {
                if (linea.find(actual->id + "," + placa) != string::npos && linea.back() == ',') {
                    linea.pop_back(); // Quitar la última coma
                    linea += actual->fechaHoraSalida;
                }
                nuevoContenido += linea + "\n";
            }
            file.close();

            ofstream outFile(archivoEspacio, ios::trunc);
            outFile << nuevoContenido;
            outFile.close();

            // Liberar el espacio
            EspacioParqueadero().liberarEspacio(actual);
            guardarDatos();

            cout << "Auto retirado del espacio " << actual->id << endl;
            return;
        }
        actual = actual->siguiente;
    } while (actual != espacios);

    cout << "No se encontró un auto con esa placa.\n";
}

void Parqueadero::mostrarEstado() {
    Nodo* actual = espacios;
    cout << "\nEstado del Parqueadero:\n";
    do {
        cout << (actual->ocupado ? "\033[31m" : "\033[0m") << "[" << actual->id << "] ";
        actual = actual->siguiente;
    } while (actual != espacios);
    cout << "\033[0m\n";
}