#include "MazeGenerator.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

MazeGenerator::MazeGenerator(int size) : size(size), maze(size, std::vector<int>(size, 0)) {}

void MazeGenerator::generateMaze() {
    srand(time(nullptr));
    
    // Inicializar todas las celdas como paredes (0)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            maze[i][j] = 0; 
        }
    }

    // Crear un camino aleatorio asegurando conectividad
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((rand() % 2 == 0) || (i == 0 && j == 0) || (i == size-1 && j == size-1)) {
                maze[i][j] = 1; // Espacio abierto
            }
        }
    }

    // Asignar entrada y salida
    maze[0][0] = 2;  // Entrada
    maze[size - 1][size - 1] = 3;  // Salida
}


void MazeGenerator::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : maze) {
        for (int cell : row) {
            file << cell << " ";  
        }
        file << "\n";
    }
    file.close();
}


const std::vector<std::vector<int>>& MazeGenerator::getMaze() const {
    return maze;
}
