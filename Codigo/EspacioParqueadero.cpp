#include "EspacioParqueadero.h"

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

void EspacioParqueadero::ocuparEspacio(Nodo* espacio, const string& placa) {
    if (espacio && !espacio->ocupado) {
        espacio->ocupado = true;
        espacio->placa = placa;
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
