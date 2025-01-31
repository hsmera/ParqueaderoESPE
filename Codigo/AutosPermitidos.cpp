/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#include <iostream>
#include <fstream>   // Para ifstream y ofstream
#include <sstream>   // Para stringstream
#include "Parqueadero.h"
#include <algorithm>
#include <list>
#include "AutosPermitidos.h"
#include "Registro.h"
#include <algorithm> // Para std::sort

AutosPermitidos::AutosPermitidos() {
    cargarDesdeArchivo();
}

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
    ofstream archivoPropietarios("Propietarios.txt", ios::app);
    if (!archivoPropietarios.is_open()) {
        cerr << "Error al abrir el archivo Propietarios.txt para guardar." << endl;
        return;
    }

    for (const auto& registro : registros) {
        if (!registro.propietario.nombre.empty() &&
            !registro.propietario.cedula.empty() &&
            !registro.propietario.correo.empty()) {
            archivoPropietarios << registro.propietario.nombre << ","
                                << registro.propietario.cedula << ","
                                << registro.propietario.correo << "\n";
        } else {
            //cerr << "Se encontró un propietario con datos incompletos. No se guardará." << endl;
        }
    }
    archivoPropietarios.close();
}

void AutosPermitidos::mostrarPropietarios() {
    ifstream archivoPropietarios("Propietarios.txt");
    if (!archivoPropietarios.is_open()) {
        cerr << "No se pudo abrir el archivo Propietarios.txt para leer." << endl;
        return;
    }

    cout << "Propietarios Registrados:\n"; // Muestra el título solo una vez
    string linea;
    while (getline(archivoPropietarios, linea)) {
        stringstream ss(linea);
        string nombre, cedula, correo;

        getline(ss, nombre, ',');
        getline(ss, cedula, ',');
        getline(ss, correo, ',');

        // Verifica si los datos están completos antes de mostrarlos
        if (!nombre.empty() && !cedula.empty() && !correo.empty()) {
            cout << "Nombre: " << nombre
                 << ", Cedula: " << cedula
                 << ", Correo: " << correo << endl;
        } else {
            cerr << "Se encontro un registro inválido en Propietarios.txt: " << linea << endl;
        }
    }

    archivoPropietarios.close();
}

void AutosPermitidos::agregarAuto(const Auto& autoPermitido, const Propietario& propietario) {
    // Verificar si la placa ya existe
    for (const auto& registro : registros) {
        if (registro.autoPermitido.placa == autoPermitido.placa) {
            cout << "El auto con placa " << autoPermitido.placa << " ya está registrado." << endl;
            return;
        }
    }

    // Verificar si la cédula ya está en la lista antes de agregar
    if (existeCedula(propietario.cedula)) {
        cout << "Error: La cedula " << propietario.cedula << " ya esta registrada y no se puede duplicar." << endl;
        return;
    }

    // Si no hay duplicados, agregar el auto y propietario
    registros.emplace_back(autoPermitido, propietario);

    // Ordenar la lista después de agregar un nuevo auto (por placa)
    registros.sort([](const Registro& a, const Registro& b) {
        return a.getAutoPermitido().getPlaca() < b.getAutoPermitido().getPlaca();
    });

    guardarEnArchivo();
    guardarPropietarios();
    cout << "Auto y propietario agregados correctamente." << endl;
}

bool AutosPermitidos::existeCedula(const string& cedula) {
    for (const auto& registro : registros) {
        if (registro.propietario.cedula == cedula) {
            return true; // La cédula ya está registrada
        }
    }
    return false; // No se encontró la cédula
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

            // Ordenar la lista después de eliminar un auto
            registros.sort([](const Registro& a, const Registro& b) {
                return a.getAutoPermitido().getPlaca() < b.getAutoPermitido().getPlaca();
            });

            guardarEnArchivo();
            cout << "Auto eliminado correctamente." << endl;
            return;
        }
    }
    cout << "No se encontró un auto con la placa " << placa << "." << endl;
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

void AutosPermitidos::ordenarAutos() {
    // Si la lista tiene 0 o 1 elementos no es necesario ordenar
    if (registros.size() <= 1) return;

    // Usamos un algoritmo de ordenación por inserción en la lista
    for (auto it = std::next(registros.begin()); it != registros.end(); ++it) {
        auto current = it;
        auto prev = std::prev(current);

        // Comparar los elementos de la lista (por ejemplo, por la placa del auto)
        while (current != registros.begin() && current->autoPermitido.placa < prev->autoPermitido.placa) {
            std::swap(*current, *prev); // Intercambiar los elementos
            --current;
            --prev;
        }
    }

    // Guardar los autos ordenados en el archivo
    guardarEnArchivo();
}

std::list<Registro>& AutosPermitidos::getRegistros(){
    return registros;
}