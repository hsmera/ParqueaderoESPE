#include "MazeGenerator.h"
#include "MazeReader.h"
#include "MazeRenderer.h"
#include <iostream>

int main() {
    int size;
    std::cout << "Ingrese el tamaño del laberinto: ";
    std::cin >> size;

    MazeGenerator generator(size);
    generator.generateMaze();
    generator.saveToFile("maze.txt");

    MazeReader reader("maze.txt");
    MazeRenderer renderer(reader.getMaze());
    renderer.render();

    return 0;
}
