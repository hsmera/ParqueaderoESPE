#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

class HashTableInt {
private:
    std::vector<int> table;
    int size;
    int metodo;

    int hash1(int key);
    int hash2(int key);
    int resolverColision(int key, int intento);

public:
    HashTableInt(int size, int metodo);
    void insertar(int key);
    bool buscar(int key);
    void eliminar(int key);
    void mostrar();
};


class HashTableString {
private:
    std::vector<std::string> table;
    int size;
    int metodo; // 0 = Lineal, 1 = Cuadrático, 2 = Doble Hashing

    int hashString(const std::string& key);
    int resolverColision(int hashValue, int intento);

public:
    HashTableString(int size, int metodo);

    void insertar(const std::string& key);
    bool buscar(const std::string& key);
    void eliminar(const std::string& key);
    void mostrar();
};
#endif
