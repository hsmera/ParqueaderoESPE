#include "Nodo.h"
#include <iostream>

Nodo::Nodo(const string& id)
    : id(id), ocupado(false), placa(""), horaIngreso(0), siguiente(nullptr), anterior(nullptr) {}

void Nodo::mostrarEstado() const {
    cout << "Espacio " << id << ": "
         << (ocupado ? "Ocupado" : "Libre")
         << ", Placa: " << (placa.empty() ? "N/A" : placa)
         << ", Hora Ingreso: " << (horaIngreso == 0 ? "N/A" : ctime(&horaIngreso)) << endl;
}
