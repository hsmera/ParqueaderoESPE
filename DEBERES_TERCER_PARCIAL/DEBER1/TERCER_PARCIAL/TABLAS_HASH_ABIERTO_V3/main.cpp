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

// Función para manejar las operaciones con enteros
void manejarEnteros() {
    int tamanio, clave;
    Validaciones<int> validador;

    tamanio = validador.ingresar("Ingrese el tamanio de la tabla hash: ", "entero");
    HashTable<int> ht(tamanio);

    // Mostrar la tabla vacía al inicio
    ht.drawTable();

    Menu menu;
    vector<string> opciones = {"Insertar", "Eliminar", "Buscar", "Mostrar", "Salir"};

    while (true) {
        int opcion = menu.mostrarMenu("Menú Tabla Hash de Enteros", opciones);

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
                return;
            default:
                cout << "Opcion no valida." << endl;
        }

        // Renderizar la tabla después de cada operación
        ht.drawTable();
    }
}

// Función para manejar las operaciones con cadenas
void manejarCadenas() {
    int tamanio;
    string clave;
    Validaciones<int> validadorInt;
    Validaciones<string> validador;

    // Obtener el tamaño de la tabla hash
    tamanio = validadorInt.ingresar("Ingrese el tamanio de la tabla hash: ", "entero");

    // Usar HashTable<string> ya que vamos a trabajar con cadenas como claves
    HashTable<string> ht(tamanio);

    // Mostrar la tabla vacía al inicio
    ht.drawTable();

    Menu menu;
    vector<string> opciones = {"Insertar", "Eliminar", "Buscar", "Mostrar", "Salir"};

    while (true) {
        int opcion = menu.mostrarMenu("Menú Tabla Hash de Cadenas", opciones);

        switch (opcion) {
            case 0:
                // Pedir al usuario una cadena para insertar
                clave = validador.ingresar("Ingrese la clave a insertar: ", "string");
                ht.insert(clave);  // Insertar la cadena en la tabla hash
                break;
            case 1:
                // Pedir al usuario una cadena para eliminar
                clave = validador.ingresar("Ingrese la clave a eliminar: ", "string");
                ht.remove(clave);  // Eliminar la cadena de la tabla hash
                pausar();
                break;
            case 2:
                // Pedir al usuario una cadena para buscar
                clave = validador.ingresar("Ingrese la clave a buscar: ", "string");
                if (ht.find(clave)) {
                    cout << "\nClave encontrada!" << endl;
                } else {
                    cout << "\nClave no encontrada." << endl;
                }
                pausar();  // Pausa tras la búsqueda
                break;
            case 3:
                ht.display();  // Mostrar el contenido de la tabla hash
                pausar();  // Pausa tras mostrar la tabla
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                return;
            default:
                cout << "Opcion no valida." << endl;
        }

        // Renderizar la tabla después de cada operación
        ht.drawTable();
    }
}

int main() {
    Menu menu;
    vector<string> opciones = {"Trabajar con Enteros", "Trabajar con Cadenas", "Salir"};

    while (true) {
        int opcion = menu.mostrarMenu("Menú Principal", opciones);

        switch (opcion) {
            case 0:
                manejarEnteros();  // Llama al submenú de enteros
                break;
            case 1:
                manejarCadenas();  // Llama al submenú de cadenas
                break;
            case 2:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opción no válida." << endl;
        }
    }

    return 0;
}
