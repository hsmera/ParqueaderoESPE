#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <conio.h>  // Para _getch()
#include "HashTable.h"

class Menu {
public:
    void mostrarMenuPrincipal();
    void manejarSubMenu(int tipoHash);
private:
    int navegarMenu(std::vector<std::string> opciones);
};

#endif
