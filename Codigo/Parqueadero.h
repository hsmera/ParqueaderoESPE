#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include <string>
#include "EspacioParqueadero.h"
#include "Auto.h"
#include "Propietario.h"
using namespace std;

class Parqueadero {
private:
    Nodo* espacios; // Lista circular de espacios de parqueo
    const int capacidad = 12; // Número de espacios
    const string archivoParqueadero = "parqueadero.txt"; 
    const string archivoEspacio = "espacio_parqueadero.txt";

public:
    Parqueadero();

    void cargarDatos();       // Carga datos desde archivos
    void guardarDatos();      // Guarda el estado en archivos
    void estacionarAuto(const Auto& autoObj, const Propietario& propietario, const string& espacioId);
    void retirarAuto(const string& placa);
    void mostrarEstado();     // Visualización gráfica
};

#endif

