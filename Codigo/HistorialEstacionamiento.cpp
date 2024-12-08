#include "HistorialEstacionamiento.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Leer todo el archivo en memoria
vector<string> HistorialEstacionamiento::leerArchivo() {
    ifstream file(archivoHistorial);
    vector<string> contenido;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de historial: " << archivoHistorial << endl;
        return contenido;
    }

    string linea;
    while (getline(file, linea)) {
        contenido.push_back(linea);
    }

    file.close();
    return contenido;
}

// Sobrescribir todo el archivo con contenido nuevo
void HistorialEstacionamiento::escribirArchivo(const vector<string>& contenido) {
    ofstream file(archivoHistorial, ios::trunc);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de historial para escritura: " << archivoHistorial << endl;
        return;
    }

    for (const string& linea : contenido) {
        file << linea << endl;
    }

    file.close();
}

// Registrar la entrada de un auto
void HistorialEstacionamiento::registrarEntrada(const Auto& autoObj, const Propietario& propietario, const string& espacioId, const string& fechaHoraIngreso) {
    vector<string> contenido = leerArchivo();
    bool placaEncontrada = false;

    for (string& linea : contenido) {
        stringstream ss(linea);
        string placa;
        getline(ss, placa, ',');

        if (placa == autoObj.getPlaca()) {
            // Agregar entrada acumulativa
            linea += espacioId + ":" + fechaHoraIngreso + "|";
            placaEncontrada = true;
            break;
        }
    }

    if (!placaEncontrada) {
        // Crear un nuevo registro si no existe la placa
        string nuevaEntrada = autoObj.getPlaca() + "," +
                              autoObj.getMarca() + "," +
                              autoObj.getColor() + "," +
                              propietario.getNombre() + "," +
                              propietario.getCedula() + "," +
                              propietario.getCorreo() + "," +
                              espacioId + ":" + fechaHoraIngreso + "|";
        contenido.push_back(nuevaEntrada);
    }

    escribirArchivo(contenido);
}

// Registrar la salida de un auto
void HistorialEstacionamiento::registrarSalida(const string& placa, const string& fechaHoraSalida) {
    vector<string> contenido = leerArchivo();
    bool actualizado = false;

    for (string& linea : contenido) {
        stringstream ss(linea);
        string p;
        getline(ss, p, ',');

        if (p == placa) {
            // Actualizar la última entrada acumulativa con la hora de salida
            size_t posUltimo = linea.find_last_of('|');
            if (posUltimo != string::npos && linea[posUltimo - 1] != '-') {
                linea.insert(posUltimo, "-" + fechaHoraSalida);
                actualizado = true;
                break;
            }
        }
    }

    if (!actualizado) {
        cerr << "Error: No se encontró una entrada activa para la placa " << placa << ".\n";
    }

    escribirArchivo(contenido);
}

// Obtener el historial de una placa
string HistorialEstacionamiento::obtenerHistorialPorPlaca(const string& placa) {
    vector<string> contenido = leerArchivo();

    for (const string& linea : contenido) {
        stringstream ss(linea);
        string p;
        getline(ss, p, ',');

        if (p == placa) {
            return linea;
        }
    }

    return "Historial no encontrado para la placa: " + placa;
}

// Mostrar el historial completo
void HistorialEstacionamiento::mostrarHistorialCompleto() {
    vector<string> contenido = leerArchivo();

    cout << "\nHistorial Completo:\n";
    for (const string& linea : contenido) {
        cout << linea << endl;
    }
}
