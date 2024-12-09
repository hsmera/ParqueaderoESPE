/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

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
    void mostrarHistorialPorFecha(const string& fecha) const;
    void mostrarHistorialPorFechaYPlaca(const string& fecha, const string& placa) const;
};

#endif // HISTORIALESTACIONAMIENTO_H
