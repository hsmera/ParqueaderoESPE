#ifndef NODORN_H
#define NODORN_H

#include <string>
using namespace std;

class NodoRN {
public:
    string placa;             // Clave principal (para búsqueda)
    string espacioId;         // ID del espacio del parqueadero
    string fechaHoraIngreso;  // Fecha y hora de ingreso
    string fechaHoraSalida;   // Fecha y hora de salida (vacía si aún está estacionado)

    bool color;               // true = rojo, false = negro
    NodoRN* padre;            // Puntero al nodo padre
    NodoRN* izquierdo;        // Puntero al hijo izquierdo
    NodoRN* derecho;          // Puntero al hijo derecho

    // Constructor
    NodoRN(const string& placa, const string& espacioId, 
           const string& fechaHoraIngreso, const string& fechaHoraSalida = "") 
        : placa(placa), espacioId(espacioId), fechaHoraIngreso(fechaHoraIngreso), 
          fechaHoraSalida(fechaHoraSalida), color(true), 
          padre(nullptr), izquierdo(nullptr), derecho(nullptr) {}
};

#endif
