#ifndef HISTORIALESTACIONAMIENTO_H
#define HISTORIALESTACIONAMIENTO_H

#include <string>
#include <vector>
#include "Auto.h"
#include "Propietario.h"

using namespace std;

class HistorialEstacionamiento {
private:
    const string archivoHistorial = "historial_estacionamiento.txt";

    // Método privado para leer todo el archivo
    vector<string> leerArchivo();

    // Método privado para escribir todo el archivo
    void escribirArchivo(const vector<string>& contenido);

public:
    void registrarEntrada(const Auto& autoObj, const Propietario& propietario, const string& espacioId, const string& fechaHoraIngreso);
    void registrarSalida(const string& placa, const string& fechaHoraSalida);
    string obtenerHistorialPorPlaca(const string& placa);
    void mostrarHistorialCompleto();
};

#endif 

