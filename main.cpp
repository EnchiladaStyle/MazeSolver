// to compile: g++ -std=c++11 -o main main.cpp Explorer.cpp Maze.cpp maze1.cpp maze2.cpp maze3.cpp
// to run: ./main

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include "Maze.h"
#include "Explorer.h"
#include "maze1.h"
#include "maze2.h"
#include "maze3.h"

int main(){

    std::vector<std::vector<std::string> > maze1Struct = maze1::getMaze();

    Maze maze1(maze1Struct);
    Explorer explorer;

    std::vector<int> currentPosition = {0, 1};
    std::promise<bool> foundEnd;
    std::future<bool> foundEndFuture = foundEnd.get_future();
    bool* done = new bool(false);
    
    std::thread initThread(&Explorer::traverseMaze, &explorer, std::ref(maze1), currentPosition[0], currentPosition[1], std::ref(foundEnd), done);

    while (foundEndFuture.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
        maze1.showMaze(false);
    }
    maze1.showMaze(true);
    
    initThread.join();




    char input;
    std::cin>>input;

    std::vector<std::vector<std::string> > maze2Struct = maze2::getMaze();
    Maze maze2(maze2Struct);
    currentPosition = {0, 1};
    std::promise<bool> foundEnd2;
    std::future<bool> foundEndFuture2 = foundEnd2.get_future();
    *done = false;

    std::thread initThread2(&Explorer::traverseMaze, &explorer, std::ref(maze2), currentPosition[0], currentPosition[1], std::ref(foundEnd2), done);

    while (foundEndFuture2.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
        maze2.showMaze(false);
    }
    maze2.showMaze(true);
    
    initThread2.join();




    std::cin>>input;

    std::vector<std::vector<std::string> > maze3Struct = maze3::getMaze();
    Maze maze3(maze3Struct);
    currentPosition = {0, 1};
    std::promise<bool> foundEnd3;
    std::future<bool> foundEndFuture3 = foundEnd3.get_future();
    *done = false;

    std::thread initThread3(&Explorer::traverseMaze, &explorer, std::ref(maze3), currentPosition[0], currentPosition[1], std::ref(foundEnd3), done);

    while (foundEndFuture3.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
        maze3.showMaze(false);
    }
    maze3.showMaze(true);
    
    initThread3.join();

}
