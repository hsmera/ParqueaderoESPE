#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem> 
#include "Validaciones.h"

using namespace std;
namespace fs = filesystem;

int procesoCount = 0;
string carpetaCapturas; 

// Asignación dinámica de la matriz tablero
int** crearTablero(int n) {
    int** tablero = new int*[n];
    for (int i = 0; i < n; i++) {
        tablero[i] = new int[n]();
    }
    return tablero;
}

// Liberación de la memoria del tablero
void liberarTablero(int** tablero, int n) {
    for (int i = 0; i < n; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;
}

// Función para verificar si es seguro colocar una reina
bool esSeguro(int** tablero, int fila, int columna, int n) {
    for (int i = 0; i < fila; i++) {
        if (*(*(tablero + i) + columna) == 1 || 
            (columna - (fila - i)) >= 0 && *(*(tablero + i) + (columna - (fila - i))) == 1 || 
            (columna + (fila - i)) < n && *(*(tablero + i) + (columna + (fila - i))) == 1) 
            return false;
    }
    return true;
}

// Función para guardar la imagen en la carpeta
void guardarImagen(sf::RenderWindow& ventana) {
    sf::Texture textura;
    textura.create(ventana.getSize().x, ventana.getSize().y);
    textura.update(ventana);
    
    sf::Image imagen = textura.copyToImage();
    string nombreArchivo = carpetaCapturas + "/paso_" + to_string(procesoCount) + ".png";
    
    if (imagen.saveToFile(nombreArchivo)) {
        cout << "Imagen guardada: " << nombreArchivo << endl;
    } else {
        cout << "Error al guardar la imagen." << endl;
    }
}

// Función para procesar la reina y cambiar su color de fondo
sf::Texture procesarReina(const sf::Texture& reinaTextura, sf::Color colorFondo) {
    sf::Image imagen = reinaTextura.copyToImage();
    for (unsigned int x = 0; x < imagen.getSize().x; x++) {
        for (unsigned int y = 0; y < imagen.getSize().y; y++) {
            sf::Color pixel = imagen.getPixel(x, y);
            if (pixel.a < 200 || (pixel.r > 200 && pixel.g > 200 && pixel.b > 200)) { 
                imagen.setPixel(x, y, colorFondo); 
            }            
        }
    }

    sf::Texture nuevaTextura;
    nuevaTextura.loadFromImage(imagen);
    return nuevaTextura;
}

// Función para dibujar el tablero y las reinas
void dibujarTablero(sf::RenderWindow& ventana, int** tablero, int n, const sf::Texture& reinaTextura, const vector<sf::Vector2i>& posicionesReinas, vector<sf::Vector2i>& ataquesReina) {
    ventana.clear();
    sf::Color colorClaro(222, 184, 135);
    sf::Color colorOscuro(139, 69, 19); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sf::RectangleShape cuadrado(sf::Vector2f(80, 80));
            cuadrado.setPosition(j * 80, i * 80);
            sf::Color colorCasilla = (i + j) % 2 == 0 ? colorClaro : colorOscuro;
            cuadrado.setFillColor(colorCasilla);
            ventana.draw(cuadrado);
        }
    }
    for (auto& posicion : posicionesReinas) {
        int x = posicion.x;
        int y = posicion.y;
        sf::Texture reinaModificada = procesarReina(reinaTextura, (x + y) % 2 == 0 ? colorClaro : colorOscuro);
        sf::Sprite reinaSprite(reinaModificada);
        reinaSprite.setScale(80.f / reinaTextura.getSize().x, 80.f / reinaTextura.getSize().y);
        reinaSprite.setPosition(x * 80, y * 80);
        ventana.draw(reinaSprite);
    }
    for (auto& ataque : ataquesReina) {
        sf::CircleShape punto(10);
        punto.setFillColor(sf::Color(255, 0, 0, 150)); 
        punto.setPosition(ataque.x * 80 + 35, ataque.y * 80 + 35); 
        ventana.draw(punto);
    }

    ventana.display();
}

void calcularAtaquesReina(int x, int y, int n, vector<sf::Vector2i>& ataquesReina) {
    ataquesReina.clear();
    for (int i = 0; i < n; i++) {
        if (i != x) ataquesReina.push_back(sf::Vector2i(i, y)); 
    }

    for (int i = 0; i < n; i++) {
        if (i != y) ataquesReina.push_back(sf::Vector2i(x, i)); 
    }

    for (int i = 1; i < n; i++) {
        if (x + i < n && y + i < n) ataquesReina.push_back(sf::Vector2i(x + i, y + i)); 
        if (x - i >= 0 && y - i >= 0) ataquesReina.push_back(sf::Vector2i(x - i, y - i)); 
        if (x + i < n && y - i >= 0) ataquesReina.push_back(sf::Vector2i(x + i, y - i)); 
        if (x - i >= 0 && y + i < n) ataquesReina.push_back(sf::Vector2i(x - i, y + i)); 
    }
}

// Algoritmo para resolver el problema de las N-Reinas
bool resolverReinas(int** tablero, int fila, int n, sf::RenderWindow& ventana, const sf::Texture& reinaTextura, vector<sf::Vector2i>& posicionesReinas) {
    if (fila == n) return true;
    for (int columna = 0; columna < n; columna++) {
        procesoCount++;
        if (esSeguro(tablero, fila, columna, n)) {
            *(*(tablero + fila) + columna) = 1; 
            posicionesReinas.push_back(sf::Vector2i(columna, fila)); 
            vector<sf::Vector2i> recorridoReinaVacío;
            dibujarTablero(ventana, tablero, n, reinaTextura, posicionesReinas, recorridoReinaVacío);
            guardarImagen(ventana);
            if (resolverReinas(tablero, fila + 1, n, ventana, reinaTextura, posicionesReinas)) return true;
            *(*(tablero + fila) + columna) = 0; 
            posicionesReinas.pop_back(); 
            dibujarTablero(ventana, tablero, n, reinaTextura, posicionesReinas, recorridoReinaVacío);
        }
    }
    return false;
}

int main() {
    Validaciones<int> validador;
    int tamanio;
    do { 
        tamanio = validador.ingresar("Ingrese el tamanio del tablero (N): ", "entero");
        cout << endl;
        if (tamanio < 1 || tamanio > 8) {
            cout << "Por favor, ingrese un valor entre 1 y 8." << endl;
        }
    } while (tamanio < 1 || tamanio > 8);

    carpetaCapturas = "Capturas_" + to_string(tamanio) + "_Reinas";
    fs::create_directory(carpetaCapturas); 

    int** tablero = crearTablero(tamanio);

    sf::Texture reinaTextura;
    if (!reinaTextura.loadFromFile("reina.png")) {
        cout << "Error al cargar la imagen de la reina." << endl;
        return -1;
    }

    sf::RenderWindow ventana(sf::VideoMode(tamanio * 80, tamanio * 80), "Problema de las N-Reinas");

    vector<sf::Vector2i> posicionesReinas;
    vector<sf::Vector2i> ataquesReina; 

    clock_t inicio = clock();
    if (resolverReinas(tablero, 0, tamanio, ventana, reinaTextura, posicionesReinas)) {
        cout << "Solucion encontrada. Procesos realizados: " << procesoCount << endl;
    } else {
        cout << "No hay solucion para el problema de las N-Reinas." << endl;
    }
    clock_t fin = clock();
    cout << "Tiempo total de ejecucion: " << double(fin - inicio) / CLOCKS_PER_SEC << " segundos." << endl;

    liberarTablero(tablero, tamanio);

    bool mostrarRecorrido = false; 

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            if (evento.type == sf::Event::MouseButtonPressed) {
                int x = evento.mouseButton.x / 80;
                int y = evento.mouseButton.y / 80;

                for (auto& posicion : posicionesReinas) {
                    if (posicion.x == x && posicion.y == y) {
                        calcularAtaquesReina(x, y, tamanio, ataquesReina);
                        break;
                    }
                }
            }
        }
        dibujarTablero(ventana, tablero, tamanio, reinaTextura, posicionesReinas, ataquesReina);
    }

    return 0;
}
