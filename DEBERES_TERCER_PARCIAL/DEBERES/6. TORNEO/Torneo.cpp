/*LaclaseTorneodefinelassgtesoperacionesparamanejaruncampeonatoporeliminación,esdecir,enqueel
jugadorquepierdequedaeliminado.
a) Escriba un método de encabezamiento void lugares(TorneoT) que muestre la clasificación completa al
 finaldel torneoTde64jugadores enlaforma:1ºX 2ºX 3ºX,X 5ºX,X,X,X 9ºX,X,X,X,X,X,X,X 17º...
 33º...enqueXeselnombredeunjugador.
 b) Escribaelmétodolugarsuponiendoquelosresultadosdel torneoseregistranenunárbolbinario.Por
 ejemplo,elsiguienteárbolbinariomuestrauntorneoentre4enqueelcampeónfueB:
     B    
  B    C  
A  B  C  D 
class Nodo { 
String valor;  
Nodo izq, der; 
} */

#include <iostream>
#include <cmath>
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

// Definición de la clase Torneo
class Torneo {
private:
    Nodo* raiz;

public:
    Torneo() : raiz(nullptr) {}

    // Método para establecer la raíz del torneo
    void setRaiz(Nodo* r) {
        raiz = r;
    }

    // Método para obtener el jugador en la posición n
    string jugador(int n) {
        return jugador(n, raiz);
    }

    string jugador(int n, Nodo* r) {
        if (r == nullptr) return "";
        if (n == 1) return r->valor;
        string izqRes = jugador(n / 2, r->izq);
        string derRes = jugador(n / 2, r->der);
        return (!izqRes.empty()) ? izqRes : derRes;
    }

    // Método para imprimir los lugares del torneo
    void lugares() {
        cout << "1o " << jugador(1) << endl;
        for (int i = 0; i <= 5; ++i) {
            int n = static_cast<int>(pow(2, i)) + 1;
            cout << n << "o " << jugador(n) << endl;
        }
    }

    // Método para obtener el lugar de un jugador en el torneo
    int lugar(string x) {
        return lugar(x, 1, raiz);
    }

    // Método recursivo para encontrar el lugar de un jugador
    int lugar(string x, int n, Nodo* r) {
        if (r == nullptr) return -1;
        if (r->valor == x) 
            return n / 2 + 1;
        return max(lugar(x, 2 * n, r->izq), lugar(x, 2 * n, r->der));
    }
};

// Ejemplo de uso
int main() {
    // Crear nodos para el torneo
    Nodo* n1 = new Nodo("Jugador1");
    Nodo* n2 = new Nodo("Jugador2");
    Nodo* n3 = new Nodo("Jugador3");
    Nodo* n4 = new Nodo("Jugador4");
    Nodo* n5 = new Nodo("Jugador5");

    // Construcción del árbol binario
    n1->izq = n2;
    n1->der = n3;
    n2->izq = n4;
    n2->der = n5;

    // Crear el torneo y asignar la raíz
    Torneo t;
    t.setRaiz(n1);

    // Imprimir los lugares del torneo
    t.lugares();

    // Buscar la posición de un jugador
    cout << "Lugar de Jugador3: " << t.lugar("Jugador3") << endl;

    // Liberar memoria
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;

    return 0;
}


