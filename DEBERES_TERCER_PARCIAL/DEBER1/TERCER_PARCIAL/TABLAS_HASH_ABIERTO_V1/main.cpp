#include "Menu.h"
#include "HashTable.h"
#include <iostream>
#include <vector>
#include "Validaciones.h"

using namespace std;

// Función para pausar la ejecución y permitir al usuario ver los resultados
void pausar() {
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    int tamanio, clave;
    Validaciones<int> validador;

    tamanio = validador.ingresar("Ingrese el tamanio de la tabla hash: ", "entero");
    HashTable ht(tamanio);

    // Mostrar la tabla vacía al inicio
    ht.drawTable();

    Menu menu;
    vector<string> opciones = {"Insertar", "Eliminar", "Buscar", "Mostrar", "Salir"};

    while (true) {
        int opcion = menu.mostrarMenu("Menu Tabla Hash Abierto", opciones);
        
        switch (opcion) {
            case 0:
                clave = validador.ingresar("Ingrese la clave a insertar: ", "entero");  
                ht.insert(clave);
                break;
            case 1:
                clave = validador.ingresar("Ingrese la clave a eliminar: ", "entero");
                ht.remove(clave);
                pausar();
                break;
            case 2:
                clave = validador.ingresar("Ingrese la clave a buscar: ", "entero");    
                if (ht.find(clave))
                    cout << "\nClave encontrada!" << endl;
                else
                    cout << "\nClave no encontrada." << endl;
                pausar(); // Pausa tras la búsqueda
                break;
            case 3:
                ht.display();
                pausar(); // Pausa tras mostrar la tabla
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opcion no valida." << endl;
        }

        // Renderizar la tabla después de cada operación
        ht.drawTable();
    }
    
    return 0;
}
