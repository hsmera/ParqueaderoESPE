#include "MazeRenderer.h"
#include <SFML/Graphics.hpp>

using namespace std;

MazeRenderer::MazeRenderer(const std::vector<std::vector<int>>& maze) : maze(maze) {}

void MazeRenderer::render() {
    int rows = maze.size();
    int cols = maze[0].size();
    int cellSize = 800 / rows;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Maze");
    window.clear(sf::Color::White);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cellSize;
            int y = i * cellSize;

            // Dibujar paredes con líneas en lugar de cuadros negros
            if (maze[i][j] != 2 && maze[i][j] != 3) { // No dibujar alrededor de entrada/salida
                if (maze[i][j] == 0) { // Pared
                    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                    cell.setPosition(x, y);
                    cell.setFillColor(sf::Color::White);
                    window.draw(cell);

                    // Dibujar bordes
                    sf::Vertex top[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color::Black), 
                                        sf::Vertex(sf::Vector2f(x + cellSize, y), sf::Color::Black)};
                    window.draw(top, 2, sf::Lines);

                    sf::Vertex left[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color::Black), 
                                         sf::Vertex(sf::Vector2f(x, y + cellSize), sf::Color::Black)};
                    window.draw(left, 2, sf::Lines);

                    sf::Vertex bottom[] = {sf::Vertex(sf::Vector2f(x, y + cellSize), sf::Color::Black), 
                                           sf::Vertex(sf::Vector2f(x + cellSize, y + cellSize), sf::Color::Black)};
                    window.draw(bottom, 2, sf::Lines);

                    sf::Vertex right[] = {sf::Vertex(sf::Vector2f(x + cellSize, y), sf::Color::Black), 
                                          sf::Vertex(sf::Vector2f(x + cellSize, y + cellSize), sf::Color::Black)};
                    window.draw(right, 2, sf::Lines);
                }
            }

            // Dibujar entrada y salida
            if (maze[i][j] == 2) { // Entrada
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(x, y);
                cell.setFillColor(sf::Color::Green);
                window.draw(cell);
            } 
            else if (maze[i][j] == 3) { // Salida
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(x, y);
                cell.setFillColor(sf::Color::Red);
                window.draw(cell);
            }
        }
    }

    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}
