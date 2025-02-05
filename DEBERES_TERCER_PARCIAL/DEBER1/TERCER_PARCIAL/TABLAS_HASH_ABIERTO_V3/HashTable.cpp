#include "HashTable.h"
#include <bitset>
#include <algorithm>

template <typename T>
HashTable<T>::HashTable(int size) : size(size), window(sf::VideoMode(800, 600), "Hash Table Visualization")
{
    table.resize(size);
    foundIndex = -1; // Inicializa como -1 (no encontrado)
}

#include "HashTable.h"

template <typename T>
int HashTable<T>::hashFunction(const T &key)
{
    if constexpr (std::is_integral<T>::value)
    {
        return key % size;
    }
    else if constexpr (std::is_same<T, std::string>::value)
    {
        return hashString(key);
    }
    return 0;
}

template <typename T>
int HashTable<T>::hashString(const std::string &clave)
{
    unsigned int hash = 0;
    std::string claveInvertida = clave;
    std::reverse(claveInvertida.begin(), claveInvertida.end());

    int index = 0;
    int totalLetras = claveInvertida.length();

    for (char c : claveInvertida)
    {
        unsigned int valor = static_cast<unsigned int>(c);

        std::string binHash = std::bitset<32>(hash).to_string();
        std::string binValor = std::bitset<32>(valor).to_string();

        std::string binSuma = sumaBinaria(binHash, binValor);

        if (index < totalLetras - 1)
        {
            std::string primeros4 = binSuma.substr(0, 4);
            for (int i = 11; i <= 14; i++)
            {
                binSuma[i] = (binSuma[i] == primeros4[i - 11]) ? '0' : '1';
            }
            binSuma = binSuma.substr(4) + "0000";
        }

        hash = std::bitset<32>(binSuma).to_ulong();
        index++;
    }

    return hash % size;
}

template <typename T>
std::string HashTable<T>::sumaBinaria(const std::string &a, const std::string &b)
{
    std::string resultado = "";
    int carry = 0;
    int i = a.length() - 1, j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        int bitA = (i >= 0) ? a[i] - '0' : 0;
        int bitB = (j >= 0) ? b[j] - '0' : 0;

        int suma = bitA + bitB + carry;
        resultado += (suma % 2) + '0';
        carry = suma / 2;

        i--;
        j--;
    }

    std::reverse(resultado.begin(), resultado.end());
    return resultado;
}

template <typename T>
void HashTable<T>::insert(const T &key)
{
    int index = hashFunction(key);
    table[index].push_back(key);
}

template <typename T>
void HashTable<T>::remove(const T &key)
{
    int index = hashFunction(key);
    auto it = std::find(table[index].begin(), table[index].end(), key);
    if (it != table[index].end())
    {
        table[index].erase(it);
        std::cout << "\nValor \"" << key << "\" eliminado correctamente.\n";
    }
    else
    {
        std::cout << "\nError: El valor \"" << key << "\" no se encuentra en la tabla.\n";
    }
}

template <typename T>
bool HashTable<T>::find(const T &key)
{
    int index = hashFunction(key);
    auto it = std::find(table[index].begin(), table[index].end(), key);

    if (it != table[index].end())
    {
        foundIndex = index;
        foundKey = key;

        // Animación sin bloquear el bucle
        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 1.0f)
        { // Mostrar por 1 segundo
            drawTable();
            sf::sleep(sf::milliseconds(100)); // Pequeño retraso sin bloquear completamente
        }

        resetHighlight();
        return true;
    }

    resetHighlight();
    return false;
}

template <typename T>
void HashTable<T>::resetHighlight()
{
    foundIndex = -1;
    foundKey = T();
}

template <typename T>
void HashTable<T>::display()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << i << ": ";
        for (const T &val : table[i])
        {
            std::cout << "\"" << val << "\" -> ";
        }
        std::cout << "NULL" << std::endl;
    }
}

template <typename T>
void HashTable<T>::drawTable()
{
    window.clear(sf::Color::White);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    int cellWidth = 60, cellHeight = 40;
    for (int i = 0; i < size; i++)
    {
        drawCell(i, cellWidth, cellHeight, font);
    }

    window.display();
}

template <typename T>
void HashTable<T>::drawCell(int index, int cellWidth, int cellHeight, sf::Font &font)
{
    // Dibuja la celda de la tabla
    sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
    cell.setPosition(50, 50 + index * cellHeight);
    cell.setOutlineThickness(2);
    cell.setOutlineColor(sf::Color::Black);
    window.draw(cell);

    // Dibuja el índice de la tabla
    sf::Text indexText;
    indexText.setFont(font);
    indexText.setString(std::to_string(index)); // Convertir el índice a string
    indexText.setCharacterSize(20);
    indexText.setFillColor(sf::Color::Black);
    indexText.setPosition(20, 50 + index * cellHeight + 10);
    window.draw(indexText);

    int x = 60;
    sf::Vector2f prevPosition;
    bool first = true;

    // Dibuja los valores dentro de cada celda
    for (const T &val : table[index])
    {
        sf::RectangleShape valCell(sf::Vector2f(cellWidth, cellHeight));
        valCell.setPosition(x, 50 + index * cellHeight);
        valCell.setOutlineThickness(2);
        valCell.setOutlineColor(sf::Color::Black);

        // Si es el valor encontrado, resaltar la celda
        if (index == foundIndex && val == foundKey)
        {
            valCell.setFillColor(sf::Color::Blue);
        }
        else
        {
            valCell.setFillColor(sf::Color::White);
        }

        window.draw(valCell);

        // Dibuja el valor dentro de la celda
        sf::Text valueText;
        valueText.setFont(font);
        if constexpr (std::is_same<T, std::string>::value)
        {
            valueText.setString(val); // No es necesario convertir si T es std::string
        }
        else
        {
            valueText.setString(std::to_string(val)); // Convertir el valor numérico a string
        }
        valueText.setCharacterSize(20);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(x + 10, 50 + index * cellHeight + 10);
        window.draw(valueText);

        // Dibuja flechas entre valores
        if (!first)
        {
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

template <typename T>
void HashTable<T>::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
        }

        // Dibuja constantemente la tabla sin bloqueos
        drawTable();
    }
}

// Necesitamos instanciar las plantillas para los tipos que vamos a usar.
template class HashTable<int>;
template class HashTable<std::string>;
