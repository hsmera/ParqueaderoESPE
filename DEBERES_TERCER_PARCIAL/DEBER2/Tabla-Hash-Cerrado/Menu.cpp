#include "Menu.h"

void Menu::mostrarMenuPrincipal() {
    while (true) {
        std::vector<std::string> opciones = {"Hash Entero", "Hash Cadena", "Salir"};
        int opcionSeleccionada = navegarMenu(opciones);

        if (opcionSeleccionada == 0) {
            manejarSubMenu(0); // Hash de Enteros
        } else if (opcionSeleccionada == 1) {
            manejarSubMenu(1); // Hash de Cadenas
        } else if (opcionSeleccionada == 2) {
            break;
        }
    }
}

void Menu::manejarSubMenu(int tipoHash) {
    std::vector<std::string> opciones = {"Sondeo Lineal", "Sondeo Cuadratico", "Doble Hashing", "Volver"};
    int opcionSeleccionada = navegarMenu(opciones);

    if (opcionSeleccionada == 3) return; // Volver al menú principal

    if (tipoHash == 0) {
        HashTableInt tabla(29, opcionSeleccionada);

        while (true) {
            std::vector<std::string> opcionesSub = {"Insertar", "Eliminar", "Buscar", "Volver"};
            int opcionAccion = navegarMenu(opcionesSub);

            if (opcionAccion == 3) break;

            int valor;
            std::cout << "Ingrese un valor entero: ";
            std::cin >> valor;

            if (opcionAccion == 0) {
                tabla.insertar(valor);
            } else if (opcionAccion == 1) {
                tabla.eliminar(valor);
            } else if (opcionAccion == 2) {
                bool encontrado = tabla.buscar(valor);
                std::cout << (encontrado ? "Elemento encontrado\n" : "Elemento NO encontrado\n");
            }

            std::cout << "\nEstado actual de la tabla:\n";
            tabla.mostrar();
            std::cout << "\nPresione cualquier tecla para continuar...";
            _getch();
        }
    } else {
        HashTableString tabla(29, opcionSeleccionada);

        while (true) {
            std::vector<std::string> opcionesSub = {"Insertar", "Eliminar", "Buscar", "Volver"};
            int opcionAccion = navegarMenu(opcionesSub);

            if (opcionAccion == 3) break;

            std::string valor;
            std::cout << "Ingrese una cadena: ";
            std::cin >> valor;

            if (opcionAccion == 0) {
                tabla.insertar(valor);
            } else if (opcionAccion == 1) {
                tabla.eliminar(valor);
            } else if (opcionAccion == 2) {
                bool encontrado = tabla.buscar(valor);
                std::cout << (encontrado ? "Elemento encontrado\n" : "Elemento NO encontrado\n");
            }

            std::cout << "\nEstado actual de la tabla:\n";
            tabla.mostrar();
            std::cout << "\nPresione cualquier tecla para continuar...";
            _getch();
        }
    }
}

int Menu::navegarMenu(std::vector<std::string> opciones) {
    int seleccion = 0;
    while (true) {
        system("cls");
        for (size_t i = 0; i < opciones.size(); ++i) {
            if (i == seleccion)
                std::cout << " > " << opciones[i] << " < \n";
            else
                std::cout << "   " << opciones[i] << "   \n";
        }

        char tecla = _getch();
        if (tecla == 72 && seleccion > 0) seleccion--;       // Flecha arriba
        if (tecla == 80 && seleccion < opciones.size() - 1) seleccion++; // Flecha abajo
        if (tecla == 13) return seleccion;                   // Enter
    }
}
