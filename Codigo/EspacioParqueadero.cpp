#include "EspacioParqueadero.h"
#include <iostream>
using namespace std;

Nodo* EspacioParqueadero::crearListaCircular(int cantidad) {
    Nodo* inicio = nullptr;
    Nodo* temp = nullptr;

    for (int i = 1; i <= cantidad; i++) {
        Nodo* nuevo = new Nodo();
        nuevo->id = (i < 10) ? "0" + to_string(i) : to_string(i);
        nuevo->ocupado = false;
        nuevo->placa = "";

        if (inicio == nullptr) {
            inicio = nuevo;
            inicio->siguiente = inicio;
            inicio->anterior = inicio;
        } else {
            temp->siguiente = nuevo;
            nuevo->anterior = temp;
            nuevo->siguiente = inicio;
            inicio->anterior = nuevo;
        }
        temp = nuevo;
    }
    return inicio;
}

Nodo* EspacioParqueadero::buscarEspacio(string id, Nodo* inicio) {
    Nodo* actual = inicio;
    do {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != inicio);
    return nullptr; // No encontrado
}


// Función para buscar una placa en los espacios ocupados
bool EspacioParqueadero::placaYaEstacionada(const string& placa, Nodo* inicio) {
    Nodo* actual = inicio;
    do {
        if (actual->ocupado && actual->placa == placa) {
            return true; // Placa ya estacionada
        }
        actual = actual->siguiente;
    } while (actual != inicio);
    return false; // Placa no encontrada
}

void EspacioParqueadero::ocuparEspacio(Nodo* espacio, const string& placa, Nodo* inicio) {
    if (!espacio) {
        return; // Espacio no válido
    }

    if (placaYaEstacionada(placa, inicio)) {
        // Mensaje informativo si es necesario
        cout << "Error: El vehículo con placa " << placa << " ya está estacionado.\n";
        return;
    }

    if (!espacio->ocupado) {
        espacio->ocupado = true;
        espacio->placa = placa;
        cout << "Espacio " << espacio->id << " ocupado con éxito por el vehículo con placa " << placa << ".\n";
    } else {
        cout << "Error: El espacio " << espacio->id << " ya está ocupado.\n";
    }
}

void EspacioParqueadero::liberarEspacio(Nodo* espacio) {
    if (espacio && espacio->ocupado) {
        espacio->ocupado = false;
        espacio->placa = "";
    }
}

string EspacioParqueadero::obtenerEstado(Nodo* inicio) {
    Nodo* actual = inicio;
    string estado;
    do {
        estado += actual->id + (actual->ocupado ? " Ocupado\n" : " Libre\n");
        actual = actual->siguiente;
    } while (actual != inicio);
    return estado;
}
