#include "HistorialEstacionamiento.h"
#include <algorithm> 

void HistorialEstacionamiento::registrarEntrada(const string& placa, const string& marca, const string& color,
                                                const string& nombrePropietario, const string& cedula, const string& correo,
                                                const string& espacioId, const string& fechaHoraEntrada) {
    ofstream file(archivoHistorial, ios::app);
    if (file.is_open()) {
        file << placa << "," << marca << "," << color << ","
             << nombrePropietario << "," << cedula << "," << correo << ","
             << espacioId << "," << fechaHoraEntrada << ",\n";
        file.close();
    } else {
        cerr << "Error al abrir el archivo del historial para registrar entrada." << endl;
    }
}

void HistorialEstacionamiento::registrarSalida(const string& placa, const string& espacioId, const string& fechaHoraSalida) {
    ifstream file(archivoHistorial);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo del historial para registrar salida." << endl;
        return;
    }

    string linea, nuevoContenido;
    bool actualizado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string datos[8]; // Placa, Marca, Color, Nombre, Cedula, Correo, EspacioID, FechaHoraEntrada
        for (int i = 0; i < 8 && getline(ss, datos[i], ','); ++i);

        if (datos[0] == placa && datos[6] == espacioId && datos[7].empty()) { // Buscar entrada sin salida
            linea.pop_back(); // Quitar la coma final
            linea += fechaHoraSalida;
            actualizado = true;
        }

        nuevoContenido += linea + "\n";
    }

    file.close();

    if (actualizado) {
        ofstream outFile(archivoHistorial, ios::trunc);
        if (outFile.is_open()) {
            outFile << nuevoContenido;
            outFile.close();
        } else {
            cerr << "Error al guardar el archivo del historial actualizado." << endl;
        }
    } else {
        cerr << "No se encontró una entrada para registrar la salida del auto con placa " << placa << "." << endl;
    }
}

void HistorialEstacionamiento::mostrarHistorialCompleto() {
    ifstream file(archivoHistorial);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo del historial para mostrar datos." << endl;
        return;
    }

    string linea;
    cout << "\nHistorial Completo:\n";
    cout << "Placa | Marca | Color | Propietario | Cedula | Correo | Espacio | Entrada | Salida\n";
    while (getline(file, linea)) {
        replace(linea.begin(), linea.end(), ',', '|');
        cout << linea << endl;
    }
    file.close();
}

bool HistorialEstacionamiento::obtenerHistorialPorPlaca(const string& placa) {
    ifstream file(archivoHistorial);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo del historial para filtrar por placa." << endl;
        return false;
    }

    string linea;
    bool encontrado = false;

    cout << "\nHistorial para la placa: " << placa << "\n";
    cout << "Placa | Marca | Color | Propietario | Cedula | Correo | Espacio | Entrada | Salida\n";

    while (getline(file, linea)) {
        if (linea.find(placa + ",") == 0) { // Línea comienza con la placa
            encontrado = true;
            replace(linea.begin(), linea.end(), ',', '|');
            cout << linea << endl;
        }
    }

    file.close();

    if (!encontrado) {
        cout << "No se encontraron registros para la placa " << placa << "." << endl;
    }

    return encontrado;
}
