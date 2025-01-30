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

#include "ArbolRN.h"
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
using namespace std;

class HistorialEstacionamiento {
private:
    ArbolRN historial;                 // Árbol Rojo-Negro para gestionar el historial
    const string archivoHistorial = "historial_estacionamiento.txt";

    string obtenerFechaHoraActual() const;  // Método para obtener la fecha y hora actual
    void cargarDesdeArchivo();              // Carga los datos del archivo al árbol
    void guardarEnArchivo();                // Guarda los datos del árbol al archivo

public:
    HistorialEstacionamiento();             // Constructor

    void registrarEntrada(const string& placa, const string& espacioId);
    void registrarSalida(const string& placa);
    void mostrarHistorial() const;
    string buscarHistorial(const string& placa) const;
    void mostrarHistorialPorFecha(const string& fecha) const;
    void mostrarHistorialPorFechaYPlaca(const string& fecha, const string& placa) const;
    void mostrarHistorialPorRangoHoras(const string& horaInicio, const string& horaFin) const;
    void mostrarPrimerIngresoPorFecha(const string& fecha) const;
    void mostrarAutosPorRangoFechas(const string& fechaInicio, const string& fechaFin) const;

};

#endif