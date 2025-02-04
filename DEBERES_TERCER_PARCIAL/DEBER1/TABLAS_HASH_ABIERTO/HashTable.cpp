// HashTable.cpp
#include "HashTable.h"

HashTable::HashTable(int size) : size(size), window(sf::VideoMode(800, 600), "Hash Table Visualization") {
    table.resize(size);
}

int HashTable::hashFunction(int key) {
    return key % size;
}

void HashTable::insert(int key) {
    int index = hashFunction(key);
    table[index].push_back(key);  // Insertar el valor en la lista correspondiente
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    auto it = std::find(table[index].begin(), table[index].end(), key);  // Buscar el valor
    if (it != table[index].end()) {
        table[index].erase(it);  // Eliminarlo si lo encontramos
    }
}

bool HashTable::find(int key) {
    int index = hashFunction(key);
    return std::find(table[index].begin(), table[index].end(), key) != table[index].end();
}

void HashTable::display() {
    for (int i = 0; i < size; i++) {
        std::cout << i << ": ";
        for (int val : table[i]) {
            std::cout << val << " -> ";
        }
        std::cout << "NULL" << std::endl;
    }
}

void HashTable::drawTable() {
    window.clear(sf::Color::White);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    int cellWidth = 60, cellHeight = 40;
    for (int i = 0; i < size; i++) {
        drawCell(i, cellWidth, cellHeight, font);
    }

    window.display();
}

void HashTable::drawCell(int index, int cellWidth, int cellHeight, sf::Font &font) {
    sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
    cell.setPosition(50, 50 + index * cellHeight);
    cell.setOutlineThickness(2);
    cell.setOutlineColor(sf::Color::Black);
    window.draw(cell);

    sf::Text indexText;
    indexText.setFont(font);
    indexText.setString(std::to_string(index));
    indexText.setCharacterSize(20);
    indexText.setFillColor(sf::Color::Black);
    indexText.setPosition(20, 50 + index * cellHeight + 10);
    window.draw(indexText);

    int x = 60;
    for (int val : table[index]) {
        sf::RectangleShape valCell(sf::Vector2f(cellWidth, cellHeight));
        valCell.setPosition(x, 50 + index * cellHeight);
        valCell.setOutlineThickness(2);
        valCell.setOutlineColor(sf::Color::Black);
        window.draw(valCell);

        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(val));
        valueText.setCharacterSize(20);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(x + 10, 50 + index * cellHeight + 10);
        window.draw(valueText);

        x += cellWidth;
    }
}

void HashTable::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        drawTable();

        // Reducir el uso de CPU evitando iteraciones extremadamente rápidas
        sf::sleep(sf::milliseconds(10));
    }
}
