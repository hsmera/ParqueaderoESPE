#include "MazeReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

MazeReader::MazeReader(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    std::vector<std::vector<int>> tempMaze;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        if (!row.empty()) {
            tempMaze.push_back(row);
        }
    }

    maze = tempMaze; // Asigna el laberinto cargado
    file.close();
}


const std::vector<std::vector<int>>& MazeReader::getMaze() const {
    return maze;
}
