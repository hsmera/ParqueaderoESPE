#ifndef HISTORIALESTACIONAMIENTO_H
#define HISTORIALESTACIONAMIENTO_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
using namespace std;

class RegistroHistorial {
public:
    string placa;
    string espacioId;
    string fechaHoraIngreso;
    string fechaHoraSalida;

    RegistroHistorial(const string& placa, const string& espacioId, 
                      const string& fechaHoraIngreso, const string& fechaHoraSalida = "")
        : placa(placa), espacioId(espacioId), fechaHoraIngreso(fechaHoraIngreso), fechaHoraSalida(fechaHoraSalida) {}
};

class HistorialEstacionamiento {
private:
    vector<RegistroHistorial> historial;
    const string archivoHistorial = "historial_estacionamiento.txt";

    string obtenerFechaHoraActual() const;
    void cargarDesdeArchivo();
    void guardarEnArchivo();

public:
    HistorialEstacionamiento();

    void registrarEntrada(const string& placa, const string& espacioId);
    void registrarSalida(const string& placa);
    void mostrarHistorial() const;
    string buscarHistorial(const string& placa) const;
};

#endif // HISTORIALESTACIONAMIENTO_H
