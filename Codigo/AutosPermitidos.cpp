#include "AutosPermitidos.h"
#include <iostream>
#include <fstream>   // Para ifstream y ofstream
#include <sstream>   // Para stringstream
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
                      << registro.autoPermitido.color << ","
                      << registro.propietario.nombre << ","
                      << registro.propietario.cedula << ","
                      << registro.propietario.correo << "\n";
    }
    archivoSalida.close();
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
    cout << "Auto agregado correctamente." << endl;
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
             << ", Color: " << registro.autoPermitido.color
             << ", Propietario: " << registro.propietario.nombre
             << ", Cedula: " << registro.propietario.cedula
             << ", Correo: " << registro.propietario.correo << endl;
    }
}
