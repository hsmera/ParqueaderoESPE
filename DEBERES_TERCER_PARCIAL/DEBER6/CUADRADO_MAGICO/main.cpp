#include "CuadradoMagico.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <conio.h> 

using namespace std;

// Función para manejar el menú con flechas
int menu(const vector<string>& options) {
    int choice = 0;
    while (true) {
        system("cls"); // Limpiar pantalla en Windows

        cout << "======= Menu de opciones =========\n\n";
        for (size_t i = 0; i < options.size(); i++) {
            if (i == choice) {
                cout << " > " << options[i] << " <\n";
            } else {
                cout << "   " << options[i] << "\n";
            }
        }

        char key = _getch(); // Captura la tecla presionada
        if (key == 72 && choice > 0) { // Flecha arriba
            choice--;
        } else if (key == 80 && choice < options.size() - 1) { // Flecha abajo
            choice++;
        } else if (key == 13) { // Enter
            return choice;
        }
    }
}

int main() {
    int tamanio;
    cout << "Ingrese el tamanio del cuadrado magico (par o impar): ";
    cin >> tamanio;

    CuadradoMagico cm(tamanio);
    vector<string> opciones = {
        "Ingresar numeros manualmente",
        "Generar numeros con incremento",
        "Salir"
    };

    int opcion;
    do {
        opcion = menu(opciones); // Obtener opción del menú interactivo

        switch (opcion) {
            case 0: // Ingresar números manualmente
                cm.ingresarNumeros();
                cm.generarCuadrado();
                cm.imprimir();
                break;
            case 1: { // Generar números con incremento
                int inicio, incremento;
                cout << "Ingrese el numero inicial: ";
                cin >> inicio;
                cout << "Ingrese el incremento: ";
                cin >> incremento;
                cm.generarNumeros(inicio, incremento);
                cm.generarCuadrado();
                cm.imprimir();
                break;
            }
            case 2: // Salir
                cout << "Saliendo del programa.\n";
                break;
        }

        if (opcion != 2) {
            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
            cin.get();
        }
    } while (opcion != 2);

    return 0;
}
