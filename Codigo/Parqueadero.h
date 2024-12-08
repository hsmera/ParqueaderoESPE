#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include <string>
#include "EspacioParqueadero.h"
#include "Auto.h"
#include "Propietario.h"

using namespace std;

class Parqueadero {
private:
    Nodo* espacios;                      // Lista circular que representa los espacios del parqueadero
    const int capacidad = 12;            // Capacidad del parqueadero
    const string archivoParqueadero = "parqueadero.txt"; // Archivo para guardar el estado del parqueadero
    const string archivoEspacio = "espacio_parqueadero.txt"; // Archivo para detalles de los espacios

    void cargarDatos();                  // Carga el estado del parqueadero desde un archivo
    void guardarDatos();                 // Guarda el estado actual del parqueadero en un archivo
    pair<Auto, Propietario> obtenerDatosPorPlaca(const string& placa); // Obtiene datos completos desde archivo externo
    string obtenerFechaHoraActual();     // Obtiene la fecha y hora actuales en formato legible

public:
    Parqueadero();                       // Constructor que inicializa el parqueadero y carga los datos

    void estacionarAuto(const Auto& autoObj, const Propietario& propietario, const string& espacioId);
                                         // Estaciona un auto en un espacio específico

    void retirarAuto(const string& placa); // Retira un auto del parqueadero usando la placa

    void mostrarEstado();                // Muestra el estado actual del parqueadero (ocupado/libre)
};

#endif // PARQUEADERO_H
