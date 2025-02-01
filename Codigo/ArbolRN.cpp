#include "ArbolRN.h"

// Constructor: inicializa el árbol con un nodo nulo
ArbolRN::ArbolRN() {
    nulo = new NodoRN("", "", "", "");
    nulo->color = false; // El nodo nulo siempre es negro
    raiz = nulo;
}

// Rotación a la izquierda
void ArbolRN::rotarIzquierda(NodoRN* x) {
    NodoRN* y = x->derecho;
    x->derecho = y->izquierdo;

    if (y->izquierdo != nulo) {
        y->izquierdo->padre = x;
    }

    y->padre = x->padre;
    if (x->padre == nullptr) {
        raiz = y;
    } else if (x == x->padre->izquierdo) {
        x->padre->izquierdo = y;
    } else {
        x->padre->derecho = y;
    }

    y->izquierdo = x;
    x->padre = y;
}

// Rotación a la derecha
void ArbolRN::rotarDerecha(NodoRN* y) {
    NodoRN* x = y->izquierdo;
    y->izquierdo = x->derecho;

    if (x->derecho != nulo) {
        x->derecho->padre = y;
    }

    x->padre = y->padre;
    if (y->padre == nullptr) {
        raiz = x;
    } else if (y == y->padre->derecho) {
        y->padre->derecho = x;
    } else {
        y->padre->izquierdo = x;
    }

    x->derecho = y;
    y->padre = x;
}

// Inserción en el Árbol Rojo-Negro
void ArbolRN::insertar(const string& placa, const string& espacioId, const string& fechaHoraIngreso, const string& fechaHoraSalida) {
    NodoRN* nuevo = new NodoRN(placa, espacioId, fechaHoraIngreso, fechaHoraSalida);
    nuevo->izquierdo = nulo;
    nuevo->derecho = nulo;

    NodoRN* y = nullptr;
    NodoRN* x = raiz;

    while (x != nulo) {
        y = x;
        if (nuevo->placa < x->placa) {
            x = x->izquierdo;
        } else {
            x = x->derecho;
        }
    }

    nuevo->padre = y;
    if (y == nullptr) {
        raiz = nuevo;
    } else if (nuevo->placa < y->placa) {
        y->izquierdo = nuevo;
    } else {
        y->derecho = nuevo;
    }

    nuevo->color = true; // El nuevo nodo siempre es rojo
    balancearInsercion(nuevo);
}

// Balanceo después de la inserción
void ArbolRN::balancearInsercion(NodoRN* nodo) {
    NodoRN* tio;

    while (nodo->padre && nodo->padre->color == true) {
        if (nodo->padre == nodo->padre->padre->izquierdo) {
            tio = nodo->padre->padre->derecho;

            if (tio->color == true) { // Caso 1: El tío es rojo
                nodo->padre->color = false;
                tio->color = false;
                nodo->padre->padre->color = true;
                nodo = nodo->padre->padre;
            } else { // Caso 2 o 3: El tío es negro
                if (nodo == nodo->padre->derecho) { // Caso 2: Triángulo
                    nodo = nodo->padre;
                    rotarIzquierda(nodo);
                }

                nodo->padre->color = false; // Caso 3: Línea
                nodo->padre->padre->color = true;
                rotarDerecha(nodo->padre->padre);
            }
        } else {
            // Simétrico al caso anterior
            tio = nodo->padre->padre->izquierdo;

            if (tio->color == true) {
                nodo->padre->color = false;
                tio->color = false;
                nodo->padre->padre->color = true;
                nodo = nodo->padre->padre;
            } else {
                if (nodo == nodo->padre->izquierdo) {
                    nodo = nodo->padre;
                    rotarDerecha(nodo);
                }

                nodo->padre->color = false;
                nodo->padre->padre->color = true;
                rotarIzquierda(nodo->padre->padre);
            }
        }
    }

    raiz->color = false; // La raíz siempre es negra
}

// Buscar un nodo en el árbol
NodoRN* ArbolRN::buscar(const string& placa) const {
    return buscarNodo(raiz, placa);
}

NodoRN* ArbolRN::buscarNodo(NodoRN* nodo, const string& placa) const {
    if (nodo == nulo || nodo->placa == placa) {
        return nodo;
    }

    if (placa < nodo->placa) {
        return buscarNodo(nodo->izquierdo, placa);
    } else {
        return buscarNodo(nodo->derecho, placa);
    }
}

// Recorrido inOrden
vector<NodoRN*> ArbolRN::obtenerInOrden() const {
    vector<NodoRN*> nodos;
    recorridoInOrden(raiz, nodos);
    return nodos;
}

void ArbolRN::recorridoInOrden(NodoRN* nodo, vector<NodoRN*>& nodos) const {
    if (nodo != nulo) {
        recorridoInOrden(nodo->izquierdo, nodos);
        nodos.push_back(nodo);
        recorridoInOrden(nodo->derecho, nodos);
    }
}

// Destructor
ArbolRN::~ArbolRN() {
    eliminarNodo(raiz);
    delete nulo;
}

void ArbolRN::eliminarNodo(NodoRN* nodo) {
    if (nodo != nulo) {
        eliminarNodo(nodo->izquierdo);
        eliminarNodo(nodo->derecho);
        delete nodo;
    }
}

void ArbolRN::imprimirArbol() const {
    if (raiz == nulo) {
        cout << "El árbol está vacío.\n";
        return;
    }

    cout << "Árbol Rojo-Negro (In-Orden):\n";
    imprimirInOrden(raiz);
    cout << endl;
}

// Función auxiliar para imprimir en orden
void ArbolRN::imprimirInOrden(NodoRN* nodo) const {
    if (nodo != nulo) {
        imprimirInOrden(nodo->izquierdo);
        cout << "Placa: " << nodo->placa << " | Espacio: " << nodo->espacioId
             << " | Ingreso: " << nodo->fechaHoraIngreso
             << " | Color: " << (nodo->color ? "Rojo" : "Negro") << endl;
        imprimirInOrden(nodo->derecho);
    }
}
