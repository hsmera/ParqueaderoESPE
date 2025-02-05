#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include <bitset>

template <typename T>
class HashTable {
private:
    std::vector<std::list<T>> table;
    int size;
    std::string a,b;
    int hashFunction(const T& key);
    int hashString(const std::string &key);
    sf::RenderWindow window;
    void drawCell(int index, int cellWidth, int cellHeight, sf::Font &font);
    
    // Variables de estado para animación
    int foundIndex; 
    T foundKey;   

public:
    HashTable(int size);
    void insert(const T& key);
    void remove(const T& key);
    bool find(const T& key);
    std::string sumaBinaria(const std::string &a, const std::string &b);
    void resetHighlight();
    void display();
    void drawTable();
    void run();
};

#endif
