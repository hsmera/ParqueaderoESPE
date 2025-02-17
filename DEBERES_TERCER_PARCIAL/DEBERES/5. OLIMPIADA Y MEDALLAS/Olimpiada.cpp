//a) UtilicelaclaseparamostrarenlapantallalosresultadosdelasOlimpíadasenlasiguienteforma:
//Lugar País Oro Plata Bronce Total 
//1 ... ... ... ... ... 
//... ... ... ... ... ... 
//n Chile ... ... ... ... 
//b) Escriba losmétodospais yoros considerandoque losdatos se representana travésdeuna lista
//enlazadadenodosconlasiguienteinformación:
//class Nodo{ 
//String pais;  
//int oros, platas, bronces;  
//Nodo sgte; 
//} 
//Importante. La lista semantiene ordenadapor lugar, es decir, en orden descendente según la
//cantidad total de medallas obtenidas.

#include <iostream>
#include <string>

using namespace std;

// Definición del nodo para la lista enlazada
class Nodo {
public:
    string pais;
    int oros, platas, bronces;
    Nodo* sgte;

    Nodo(string p, int o, int p_, int b) : pais(p), oros(o), platas(p_), bronces(b), sgte(nullptr) {}
};

// Definición de la clase Olimpiada
class Olimpiada {
private:
    Nodo* primero;

public:
    Olimpiada() : primero(nullptr) {}

    // Método para agregar un país con sus medallas
    void agregar(string pais, int oros, int platas, int bronces) {
        Nodo* nuevo = new Nodo(pais, oros, platas, bronces);
        nuevo->sgte = primero;
        primero = nuevo;
    }

    // Método para encontrar el lugar del país en la lista
    int lugar(string x) {
        Nodo* r = primero;
        int pos = 1;
        while (r != nullptr) {
            if (r->pais == x) 
                return pos;
            r = r->sgte;
            pos++;
        }
        return -1; // No encontrado
    }

    // Método para obtener la cantidad de oros de un país
    int oros(string x) {
        Nodo* r = primero;
        while (r != nullptr && r->pais != x)
            r = r->sgte;
        return (r != nullptr) ? r->oros : 0;
    }

    // Método para obtener la cantidad de platas de un país
    int platas(string x) {
        Nodo* r = primero;
        while (r != nullptr && r->pais != x)
            r = r->sgte;
        return (r != nullptr) ? r->platas : 0;
    }

    // Método para obtener la cantidad de bronces de un país
    int bronces(string x) {
        Nodo* r = primero;
        while (r != nullptr && r->pais != x)
            r = r->sgte;
        return (r != nullptr) ? r->bronces : 0;
    }

    // Método para obtener el país en la posición x
    string pais(int x) {
        Nodo* r = primero;
        for (int i = 1; i < x && r != nullptr; ++i)
            r = r->sgte;
        return (r != nullptr) ? r->pais : "";
    }

    // Liberar memoria
    ~Olimpiada() {
        while (primero != nullptr) {
            Nodo* temp = primero;
            primero = primero->sgte;
            delete temp;
        }
    }
};

int main() {
    Olimpiada O;

    // Agregamos algunos países con datos ficticios
    O.agregar("Chile", 2, 3, 1);
    O.agregar("Argentina", 3, 2, 4);
    O.agregar("Brasil", 5, 6, 7);

    // Buscar información de Chile
    int l = O.lugar("Chile");
    for (int i = 1; i <= l; ++i) {
        string pais = O.pais(i);
        int o = O.oros(pais);
        int p = O.platas(pais);
        int b = O.bronces(pais);
        cout << i << " " << pais << " " << o << " " << p << " " << b << " " << (o + p + b) << endl;
    }

    return 0;
}
