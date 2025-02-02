#include "ArbolRN.h"
#include <iostream>
#include <queue>  // Para recorrido por niveles
#include <iomanip>  // Para formato de impresión
#include <cmath>
#include <vector>

// Definición de colores para la consola
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"

using namespace std;

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

void ArbolRN::imprimirArbolVertical() const {
    if (raiz == nulo) {
        cout << "El árbol está vacío.\n";
        return;
    }

    // Cola para el recorrido por niveles
    queue<pair<NodoRN*, int>> cola;
    cola.push({raiz, 0});  // Nodo con su nivel

    // Variables para determinar la altura máxima del árbol
    int altura = 0;
    while (!cola.empty()) {
        NodoRN* actual = cola.front().first;
        int nivel = cola.front().second;
        cola.pop();

        altura = max(altura, nivel);  // Actualizar la altura máxima

        if (actual->izquierdo != nulo) cola.push({actual->izquierdo, nivel + 1});
        if (actual->derecho != nulo) cola.push({actual->derecho, nivel + 1});
    }

    // Depuración: Mostrar la altura del árbol
    cout << "Altura del árbol: " << altura << endl;

    // Cola para la impresión
    queue<pair<NodoRN*, int>> colaImpresion;
    cola.push({raiz, 0});  // Nodo raíz

    // Espaciado fijo entre nodos
    int espacioBase = 1;  // Reducido a 1 para más cercanía

    // Recorrer el árbol nivel por nivel
    for (int nivel = 0; nivel <= altura; ++nivel) {
        // Imprimir el nivel actual
        cout << "Nivel " << nivel << ": ";

        int tamanoNivel = cola.size();

        // Ajustar el espaciado entre nodos en niveles más profundos
        int nivelEspaciado = espacioBase * (altura - nivel + 1);  // Menos espaciado a medida que bajamos

        while (tamanoNivel > 0) {
            pair<NodoRN*, int> nodoNivel = cola.front();
            cola.pop();

            NodoRN* actual = nodoNivel.first;
            int nivelNodo = nodoNivel.second;

            if (nivelNodo == nivel) {
                // Si estamos en el primer nivel (raíz), colocarla centrada
                if (nivel == 0) {
                    cout << setw(altura * 2) << (actual->color ? RED : WHITE) << actual->espacioId << RESET;
                } else {
                    // Imprimir el nodo con color y espaciado
                    cout << setw(nivelEspaciado) << (actual->color ? RED : WHITE) << actual->espacioId << RESET;
                }
            }

            // Agregar los hijos a la cola si no son nulos
            if (actual->izquierdo != nulo) cola.push({actual->izquierdo, nivelNodo + 1});
            if (actual->derecho != nulo) cola.push({actual->derecho, nivelNodo + 1});

            tamanoNivel--;
        }
        cout << endl; // Nueva línea para el siguiente nivel
    }
}

void ArbolRN::recorridoPreorden(NodoRN* nodo) const {
    if (nodo == nulo) return;
    
    // Mostrar el nodo actual
    cout << "(" << (nodo->color ? RED : WHITE) << nodo->espacioId << RESET << ") - ";
    
    // Recorrer primero el subárbol izquierdo
    recorridoPreorden(nodo->izquierdo);
    
    // Luego el subárbol derecho
    recorridoPreorden(nodo->derecho);
}

void ArbolRN::recorridoInorden(NodoRN* nodo) const {
    if (nodo == nulo) return;
    
    // Recorrer primero el subárbol izquierdo
    recorridoInorden(nodo->izquierdo);
    
    // Mostrar el nodo actual
    cout << "(" << (nodo->color ? RED : WHITE) << nodo->espacioId << RESET << ") - ";
    
    // Luego el subárbol derecho
    recorridoInorden(nodo->derecho);
}

void ArbolRN::recorridoPostorden(NodoRN* nodo) const {
    if (nodo == nulo) return;
    
    // Recorrer primero el subárbol izquierdo
    recorridoPostorden(nodo->izquierdo);
    
    // Luego el subárbol derecho
    recorridoPostorden(nodo->derecho);
    
    // Mostrar el nodo actual
    cout << "(" << (nodo->color ? RED : WHITE) << nodo->espacioId << RESET << ") - ";
}

void ArbolRN::mostrarRecorridos() const {
    cout << "\nRecorrido Preorden: ";
    recorridoPreorden(raiz);
    cout << "\n";
    
    cout << "\nRecorrido Inorden: ";
    recorridoInorden(raiz);
    cout << "\n";
    
    cout << "\nRecorrido Postorden: ";
    recorridoPostorden(raiz);
    cout << "\n";
}