#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <vector>
#include <string>

class MazeGenerator {
private:
    int size;
    std::vector<std::vector<int>> maze;

public:
    MazeGenerator(int size);
    void generateMaze();
    void saveToFile(const std::string& filename);
    const std::vector<std::vector<int>>& getMaze() const;
};

#endif // MAZE_GENERATOR_H
