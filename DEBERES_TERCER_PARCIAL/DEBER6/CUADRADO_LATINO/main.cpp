#include "CuadradoLatino.h"
#include "Validaciones.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>

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

        char key = _getch();
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
    Validaciones<int> validador;
    int tamanio;
    do {
        tamanio = validador.ingresar("Ingrese el tamanio del cuadrado latino (minimo 2): ", "entero");
    } while (tamanio < 2);
    
    CuadradoLatino cl(tamanio);

    vector<string> opciones = {
        "Ingresar numeros manualmente",
        "Generar numeros con incremento",
        "Salir"
    };

    int opcion;
    do {
        opcion = menu(opciones);

        switch (opcion) {
            case 0: // Ingresar números manualmente
                cl.ingresarNumeros();
                break;
            case 1: { // Generar números con incremento
                int inicio, incremento;
                inicio = validador.ingresar("Ingrese el numero inicial: ", "entero");
                cout << endl;
                incremento = validador.ingresar("Ingrese el incremento: ", "entero");
                cout << endl;
                cl.generarNumeros(inicio, incremento);
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
