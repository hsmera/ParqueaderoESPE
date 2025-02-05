// HashTable.cpp
#include "HashTable.h"

HashTable::HashTable(int size) : size(size), window(sf::VideoMode(800, 600), "Hash Table Visualization") {
    table.resize(size);
    foundIndex = -1; // Inicializa como -1 (no encontrado)
    foundKey = -1;
}

int HashTable::hashFunction(int key) {
    return key % size;
}

void HashTable::insert(int key) {
    int index = hashFunction(key);
    table[index].push_back(key);
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    auto it = std::find(table[index].begin(), table[index].end(), key);
    if (it != table[index].end()) {
        table[index].erase(it);
        std::cout << "\nValor " << key << " eliminado correctamente.\n";
    } else {
        std::cout << "\nError: El valor " << key << " no se encuentra en la tabla.\n";
    }
}

bool HashTable::find(int key) {
    int index = hashFunction(key);
    auto it = std::find(table[index].begin(), table[index].end(), key);
    if (it != table[index].end()) {
        foundIndex = index;
        foundKey = key;
        drawTable(); // Refrescar la tabla con el valor resaltado
        sf::sleep(sf::seconds(1)); // Mostrar resaltado por 1 segundo
        resetHighlight(); // Quitar resaltado después de un momento
        return true;
    }
    foundIndex = -1;
    foundKey = -1;
    return false;
}


void HashTable::resetHighlight() {
    foundIndex = -1;
    foundKey = -1;
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
    sf::Vector2f prevPosition;
    bool first = true;

    for (int val : table[index]) {
        sf::RectangleShape valCell(sf::Vector2f(cellWidth, cellHeight));
        valCell.setPosition(x, 50 + index * cellHeight);
        valCell.setOutlineThickness(2);
        valCell.setOutlineColor(sf::Color::Black);

        if (index == foundIndex && val == foundKey) {
            valCell.setFillColor(sf::Color::Blue);
        } else {
            valCell.setFillColor(sf::Color::White);
        }

        window.draw(valCell);

        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(val));
        valueText.setCharacterSize(20);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(x + 10, 50 + index * cellHeight + 10);
        window.draw(valueText);

        // Dibujar flechas entre valores
        if (!first) {
            sf::VertexArray arrow(sf::Lines, 2);
            arrow[0].position = prevPosition + sf::Vector2f(cellWidth, cellHeight / 2);
            arrow[0].color = sf::Color::Black;
            arrow[1].position = sf::Vector2f(x, 50 + index * cellHeight + cellHeight / 2);
            arrow[1].color = sf::Color::Black;
            window.draw(arrow);
        }

        prevPosition = sf::Vector2f(x, 50 + index * cellHeight);
        first = false;

        x += cellWidth + 20; // Espacio adicional para la flecha
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
        sf::sleep(sf::milliseconds(10));
    }
}
