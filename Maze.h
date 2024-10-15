#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>

class Maze {
    public:
        Maze(std::vector<std::vector<std::string> >_maze);
        void showMaze(bool foundEnd);
        bool isOpen(int x, int y);
};


#endif