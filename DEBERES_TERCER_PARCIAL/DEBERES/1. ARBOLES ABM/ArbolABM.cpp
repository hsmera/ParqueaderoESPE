//Un ABM es un árbol binario que en su raíz guarda el menor valor (y los árboles izquierdo y derecho tienen la misma propiedad).Por ejemplo,el siguienteár bol binarioes un ABM:
//         2 
//     5       4 
//8        5        7 

#include <iostream>
using namespace std;

class Nodo {
public:
    int valor;
    Nodo* izq;
    Nodo* der;

    Nodo(int x, Nodo* y = nullptr, Nodo* z = nullptr) {
        valor = x;
        izq = y;
        der = z;
    }
};

//a) Escribir un método de en cabezamiento:boolean esABM(Nodo x) que entregue true si el árbol binario de raíz x corresponde a un ABM(ofalsesino)
bool esABM(Nodo* x) {
    if (x == nullptr)
        return true;
    if (x->izq == nullptr && x->der == nullptr)
        return true;
    if (x->izq == nullptr)
        return x->valor <= x->der->valor && esABM(x->der);
    if (x->der == nullptr)
        return x->valor <= x->izq->valor && esABM(x->izq);
    return x->valor <= x->izq->valor && x->valor <= x->der->valor && esABM(x->izq) && esABM(x->der);
}

////b) Escribir un método de en cabezamiento: Nodo juntar(Nodo x, Nodo y), que entregue un nuevo ABM uniendolos ABMs de raices x e y
Nodo* juntar(Nodo* x, Nodo* y) {
    if (x == nullptr && y == nullptr)
        return nullptr;
    if (x == nullptr)
        return new Nodo(y->valor, juntar(y->izq, nullptr), juntar(y->der, nullptr));
    if (y == nullptr)
        return new Nodo(x->valor, juntar(x->izq, nullptr), juntar(x->der, nullptr));
    if (x->valor <= y->valor)
        return new Nodo(x->valor, juntar(x->izq, x->der), juntar(y, nullptr));
    else
        return new Nodo(y->valor, juntar(x, nullptr), juntar(y->izq, y->der));
}

int main() {
    Nodo* root1 = new Nodo(3, new Nodo(5), new Nodo(7));
    Nodo* root2 = new Nodo(2, new Nodo(4), new Nodo(6));
    Nodo* merged = juntar(root1, root2);

    cout << "El arbol combinado es ABM: " << (esABM(merged) ? "Si" : "No") << endl;
    return 0;
}
