#ifndef HISTORIALESTACIONAMIENTO_H
#define HISTORIALESTACIONAMIENTO_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class HistorialEstacionamiento {
private:
    const string archivoHistorial = "historial_estacionamiento.txt";

public:
    void registrarEntrada(const string& placa, const string& marca, const string& color,
                          const string& nombrePropietario, const string& cedula, const string& correo,
                          const string& espacioId, const string& fechaHoraEntrada);

    void registrarSalida(const string& placa, const string& espacioId, const string& fechaHoraSalida);

    void mostrarHistorialCompleto();

    bool obtenerHistorialPorPlaca(const string& placa);
};

#endif
