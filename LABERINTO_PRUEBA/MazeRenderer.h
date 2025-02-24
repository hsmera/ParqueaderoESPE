#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include <vector>
#include <SFML/Graphics.hpp>

class MazeRenderer {
private:
    std::vector<std::vector<int>> maze;
public:
    MazeRenderer(const std::vector<std::vector<int>>& maze);
    void render();
};

#endif // MAZE_RENDERER_H
