/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#include "AutosPermitidos.h"
#include <iostream>
#include <fstream>   
#include <sstream>   
#include "Registro.h"

// Constructor: carga los datos desde el archivo
AutosPermitidos::AutosPermitidos() {
    cargarDesdeArchivo();
}

Registro::Registro(const Auto& autoPermitido, const Propietario& propietario)
    : autoPermitido(autoPermitido), propietario(propietario) {}

// Cargar autos permitidos desde el archivo
void AutosPermitidos::cargarDesdeArchivo() {
    ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        cerr << "No se pudo abrir el archivo " << archivo << ". Creando uno nuevo." << endl;
        return;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string placa, marca, color, nombre, cedula, correo;

        getline(ss, placa, ',');
        getline(ss, marca, ',');
        getline(ss, color, ',');
        getline(ss, nombre, ',');
        getline(ss, cedula, ',');
        getline(ss, correo, ',');

        Auto autoPermitido(placa, marca, color);
        Propietario propietario(nombre, cedula, correo);
        registros.emplace_back(autoPermitido, propietario);
    }
    archivoEntrada.close();
}

// Guardar autos permitidos en el archivo
void AutosPermitidos::guardarEnArchivo() {
    ofstream archivoSalida(archivo, ios::trunc);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo " << archivo << " para guardar." << endl;
        return;
    }

    for (const auto& registro : registros) {
        archivoSalida << registro.autoPermitido.placa << ","
                      << registro.autoPermitido.marca << ","
                      << registro.autoPermitido.color << "\n";
    }
    archivoSalida.close();
}

void AutosPermitidos::guardarPropietarios() {
    ofstream archivoPropietarios("Propietarios.txt", ios::trunc);
    if (!archivoPropietarios.is_open()) {
        cerr << "Error al abrir el archivo Propietarios.txt para guardar." << endl;
        return;
    }

    for (const auto& registro : registros) {
        archivoPropietarios << registro.propietario.nombre << ","
                            << registro.propietario.cedula << ","
                            << registro.propietario.correo << "\n";
    }
    archivoPropietarios.close();
}

void AutosPermitidos::mostrarPropietarios() {
    ifstream archivoPropietarios("Propietarios.txt");
    if (!archivoPropietarios.is_open()) {
        cerr << "No se pudo abrir el archivo Propietarios.txt para leer." << endl;
        return;
    }

    string linea;
    while (getline(archivoPropietarios, linea)) {
        stringstream ss(linea);
        string nombre, cedula, correo;

        getline(ss, nombre, ',');
        getline(ss, cedula, ',');
        getline(ss, correo, ',');
        cout<< "Propietarios Registrados: "<<endl;
        cout << "Nombre: " << nombre
             << ", Cedula: " << cedula
             << ", Correo: " << correo << endl;
    }

    archivoPropietarios.close();
}

// Agregar un nuevo auto permitido
void AutosPermitidos::agregarAuto(const Auto& autoPermitido, const Propietario& propietario) {
    for (const auto& registro : registros) {
        if (registro.autoPermitido.placa == autoPermitido.placa) {
            cout << "El auto con placa " << autoPermitido.placa << " ya esta registrado." << endl;
            return;
        }
    }

    registros.emplace_back(autoPermitido, propietario);
    guardarEnArchivo();
    guardarPropietarios();
    cout << "Auto y propietario agregados correctamente." << endl;
}

// Buscar un auto por placa
bool AutosPermitidos::buscarAuto(const string& placa) const {
    for (const auto& registro : registros) {
        if (registro.autoPermitido.placa == placa) {
            return true;
        }
    }
    return false;
}

// Eliminar un auto permitido por placa
void AutosPermitidos::eliminarAuto(const string& placa) {
    for (auto it = registros.begin(); it != registros.end(); ++it) {
        if (it->autoPermitido.placa == placa) {
            registros.erase(it);
            guardarEnArchivo();
            cout << "Auto eliminado correctamente." << endl;
            return;
        }
    }
    cout << "No se encontro un auto con la placa " << placa << "." << endl;
}

// Mostrar todos los autos permitidos
void AutosPermitidos::mostrarAutos() const {
    if (registros.empty()) {
        cout << "No hay autos permitidos registrados." << endl;
        return;
    }

    cout << "Autos Permitidos:\n";
    for (const auto& registro : registros) {
        cout << "Placa: " << registro.autoPermitido.placa
             << ", Marca: " << registro.autoPermitido.marca
             << ", Color: " << registro.autoPermitido.color<< endl;
    }
}
void AutosPermitidos::mostrarAutoPorPlaca(const string& placa) const {
    bool encontrado = false;

    for (const auto& registro : registros) {
        if (registro.autoPermitido.placa == placa) {
            cout << "Auto encontrado:\n"
                 << "Placa: " << registro.autoPermitido.placa
                 << ", Marca: " << registro.autoPermitido.marca
                 << ", Color: " << registro.autoPermitido.color<< endl;
            encontrado = true;
            break;  // Asume que solo hay un auto por placa
        }
    }

    if (!encontrado) {
        cout << "No se encontro un auto con la placa " << placa << "." << endl;
    }
}
