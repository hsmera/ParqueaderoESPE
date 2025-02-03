#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <conio.h>
#include "Backup.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include "Validaciones.h"

using namespace std;
namespace fs = filesystem;

string Backup::obtenerNombreBackup() {
    auto now = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(now);
    struct tm tiempo;
    localtime_s(&tiempo, &tiempoActual);

    stringstream nombre;
    nombre << "Backup-"
           << put_time(&tiempo, "%Y-%m-%d-%H-%M-%S");

    return nombre.str();
}

void Backup::realizarBackupTodos() {
    string carpetaBase = "../backup";  // Carpeta principal de backups
    string carpetaDestino = carpetaBase + "/" + obtenerNombreBackup(); // Nueva subcarpeta con fecha y hora

    if (!fs::exists(carpetaBase)) {
        fs::create_directory(carpetaBase);
    }
    fs::create_directory(carpetaDestino);

    string carpetaOrigen = "../Codigo"; // Donde están los archivos originales

    for (const auto& archivo : fs::directory_iterator(carpetaOrigen)) {
        if (archivo.is_regular_file()) { // Evita copiar subcarpetas
            fs::copy(archivo.path(), carpetaDestino + "/" + archivo.path().filename().string(), fs::copy_options::overwrite_existing);
        }
    }

    cout << "Backup realizado en '" << carpetaDestino << "'.\n";
}

void Backup::realizarBackupEspecifico() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo a respaldar: ";
    cin >> nombreArchivo;

    string origen = "../Codigo/" + nombreArchivo;
    string carpetaBase = "../backup";  
    string carpetaDestino = carpetaBase + "/" + obtenerNombreBackup(); 

    if (!fs::exists(carpetaBase)) {
        fs::create_directory(carpetaBase);
    }
    fs::create_directory(carpetaDestino);

    string destino = carpetaDestino + "/" + nombreArchivo;
    
    if (fs::exists(origen)) {
        fs::copy(origen, destino, fs::copy_options::overwrite_existing);
        cout << "Backup del archivo '" << nombreArchivo << "' realizado en '" << carpetaDestino << "'.\n";
    } else {
        cout << "El archivo no existe en '../Codigo/'.\n";
    }
}

void Backup::eliminarArchivo() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo original a eliminar: ";
    cin >> nombreArchivo;

    string rutaArchivo = "./" + nombreArchivo;
    
    if (fs::exists(rutaArchivo)) {
        fs::remove(rutaArchivo);
        cout << "Archivo eliminado correctamente.\n";
    } else {
        cout << "El archivo no existe en 'Codigo/'.\n";
    }
}

void Backup::recuperarBackup() {
    Validaciones<int> validador;
    string carpetaBase = "../backup";

    if (!fs::exists(carpetaBase) || fs::is_empty(carpetaBase)) {
        cout << "No hay backups disponibles.\n";
        return;
    }

    vector<string> carpetas;
    cout << "Backups disponibles:\n";
    int index = 1;

    for (const auto& entry : fs::directory_iterator(carpetaBase)) {
        if (entry.is_directory()) {
            carpetas.push_back(entry.path().filename().string());
            cout << index << ". " << carpetas.back() << "\n";
            index++;
        }
    }

    int seleccion = validador.ingresar("Seleccione el numero de la carpeta a restaurar: ", "entero");
    cout << endl;

    if (seleccion < 1 || seleccion > carpetas.size()) {
        cout << "Selección invalida.\n";
        return;
    }

    string carpetaSeleccionada = carpetaBase + "/" + carpetas[seleccion - 1];

    for (const auto& archivo : fs::directory_iterator(carpetaSeleccionada)) {
        string destino = "../Codigo/" + archivo.path().filename().string();

        // Verificar si el archivo ya existe en el destino
        if (fs::exists(destino)) {
            char respuesta;
            cout << "El archivo '" << archivo.path().filename().string() << "' ya existe.\n";
            cout << "Desea reemplazarlo? (S/N): ";
            cin >> respuesta;

            if (respuesta != 'S' && respuesta != 's') {
                cout << "No se reemplazará el archivo. Continuando con el resto.\n";
                continue; // Salta al siguiente archivo si el usuario no desea reemplazarlo
            }else{
                fs::remove(destino);
            }
        }

        try {
            fs::copy(archivo.path(), destino, fs::copy_options::overwrite_existing);
            cout << "Archivo '" << archivo.path().filename().string() << "' restaurado.\n";
        } catch (const fs::filesystem_error& e) {
            cout << "Error al restaurar " << archivo.path().filename().string() << ": " << e.what() << endl;
        }
    }

    cout << "Backup restaurado desde '" << carpetaSeleccionada << "' a '../Codigo/'.\n";
}

