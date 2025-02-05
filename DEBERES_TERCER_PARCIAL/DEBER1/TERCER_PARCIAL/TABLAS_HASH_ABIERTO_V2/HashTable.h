// HashTable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

class HashTable {
private:
    std::vector<std::list<int>> table;
    int size;
    int hashFunction(int key);
    sf::RenderWindow window;
    void drawCell(int index, int cellWidth, int cellHeight, sf::Font &font);  // Nueva función
    private:
    int foundIndex; // Índice donde se encontró el valor
    int foundKey;   // Clave encontrada

public:
    HashTable(int size);
    void insert(int key);
    void remove(int key);
    bool find(int key);
    void resetHighlight();
    void display();
    void drawTable();
    void run();
};

#endif
