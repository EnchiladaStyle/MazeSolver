#ifndef EXPLORER_H
#define EXPLORER_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include "Maze.h"

class Explorer{
    public:
        std::vector<int> moveLeft(Maze& maze, int x, int y);
        std::vector<int> moveRight(Maze& maze, int x, int y);
        std::vector<int> moveDown(Maze& maze, int x, int y);
        std::vector<int> moveUp(Maze& maze, int x, int y);
        void traverseMaze(Maze& maze, int x, int y, std::promise<bool>& returnValue, bool* done);
};

#endif