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
#include <iomanip>
#include "NodoRN.h"
#include <map>

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
    bool registrarSalida(const string& placa);
    void mostrarHistorial() const;
    string buscarHistorial(const string& placa) const;
    NodoRN* buscarNodoID(NodoRN* nodo, const string& espacioId) const;
    void mostrarHistorialPorFecha(const string& fecha) const;
    void mostrarHistorialPorFechaYPlaca(const string& fecha, const string& placa) const;
    void mostrarHistorialPorRangoHoras(const string& horaInicio, const string& horaFin) const;
    void mostrarPrimerIngresoPorFecha(const string& fecha) const;
    void mostrarAutosPorRangoFechas(const string& fechaInicio, const string& fechaFin) const;
    void buscarAutosEnEspacioPorRangoFechas(const string& espacioId, const string& fechaInicio, const string& fechaFin) const ;
    void mostrarAutosPorDuracionEnFecha(const string& fecha, const string& duracionMin, const string& duracionMax) const;
    string calcularDuracion(const string& ingreso, const string& salida) const;
    bool estaEnRangoDuracion(const string& duracion, const string& duracionMin, const string& duracionMax) const;
    void mostrarEspacioMasMenosTiempoOcupado() const ;
    void mostrarEspacioMasMenosOcupado() const;
    void imprimirArbol();
    void mostrarRecorridos() const;
    int obtenerAltura(NodoRN* nodo) const;
    int obtenerAlturaNegra(NodoRN* nodo) const;
    NodoRN* obtenerRaiz();
    int obtenerProfundidad(NodoRN* nodo);
};

#endif