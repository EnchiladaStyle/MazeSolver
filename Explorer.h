#ifndef EXPLORER_H
#define EXPLORER_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>

class Explorer{
    public:
        std::vector<int> moveLeft(std::vector<std::vector<std::string> >&maze, int x, int y);
        std::vector<int> moveRight(std::vector<std::vector<std::string> >&maze, int x, int y);
        std::vector<int> moveDown(std::vector<std::vector<std::string> >&maze, int x, int y);
        std::vector<int> moveUp(std::vector<std::vector<std::string> >&maze, int x, int y);
        void traverseMaze(std::vector<std::vector<std::string> >& maze, int x, int y, std::promise<bool>& returnValue);
};

#endif