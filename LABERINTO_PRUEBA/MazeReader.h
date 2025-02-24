#ifndef MAZE_READER_H
#define MAZE_READER_H

#include <vector>
#include <string>

class MazeReader {
private:
    std::vector<std::vector<int>> maze;
public:
    MazeReader(const std::string& filename);
    const std::vector<std::vector<int>>& getMaze() const;
};

#endif // MAZE_READER_H
