//Dosárbolesbinariosson“espejos”si tienenlaformaindicadaenelsiguienteejemplo:
//      A                           A 
//    /  \                        /   \ 
//   B    C                      C     B 
//  /     / \                   / \     \ 
// D     E   F                 F   E     D 
//Escribir unmétodorecursivoquereciba las raícesdedosárbolesbinariosyentregue truesi sonespejoso false sino lo son

#include <iostream>
#include <string>

using namespace std;

// Definición del nodo del árbol binario
class Nodo {
public:
    string valor;
    Nodo* izq;
    Nodo* der;

    Nodo(string v) : valor(v), izq(nullptr), der(nullptr) {}
};

// Función para verificar si dos árboles son espejos
bool espejos(Nodo* x, Nodo* y) {
    // Caso dos árboles vacíos
    if (x == nullptr && y == nullptr)
        return true;

    // Caso un árbol vacío
    if (x == nullptr || y == nullptr)
        return false;

    // Caso ningún árbol vacío
    return (x->valor == y->valor) &&
           espejos(x->izq, y->der) &&
           espejos(x->der, y->izq);
}

// Ejemplo de uso
int main() {
    // Crear nodos para dos árboles espejo
    Nodo* a1 = new Nodo("A");
    Nodo* a2 = new Nodo("B");
    Nodo* a3 = new Nodo("C");

    Nodo* b1 = new Nodo("A");
    Nodo* b2 = new Nodo("C");
    Nodo* b3 = new Nodo("B");

    // Construcción de árboles espejos
    a1->izq = a2;
    a1->der = a3;

    b1->izq = b3;
    b1->der = b2;

    // Verificación de espejos
    if (espejos(a1, b1))
        cout << "Los árboles son espejos." << endl;
    else
        cout << "Los árboles no son espejos." << endl;

    // Liberar memoria
    delete a1;
    delete a2;
    delete a3;
    delete b1;
    delete b2;
    delete b3;

    return 0;
}
