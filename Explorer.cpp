
#include "Explorer.h"


    std::vector<int> Explorer::moveLeft(Maze& maze, int x, int y){

        if (x > 1 && maze.isOpen(x-1, y)){

            maze.layout[y][x-1] = "\u2190"; 
            return {x-1, y};
        }
        else{
            return {x, y};
        }

    }

    std::vector<int> Explorer::moveRight(Maze& maze, int x, int y){

        if (x < maze.layout[y].size() && maze.isOpen(x+1, y)){
        
            maze.layout[y][x+1] = "\u2192"; 
            return {x+1, y};
        }
        else{
            return {x, y};
        }

    }

    std::vector<int> Explorer::moveDown(Maze& maze, int x, int y){
 
        if (y < maze.layout.size() && maze.isOpen(x, y+1)){

            maze.layout[y+1][x] = "\u2193"; 
            return {x, y+1};
        }
        else{
            return {x, y};
        }

    }       

    std::vector<int> Explorer::moveUp(Maze& maze, int x, int y){

        if (y > 1 && maze.isOpen(x, y-1)){

            maze.layout[y-1][x] = "\u2191"; 
            return {x, y-1};
        }
        else{
            return {x, y};
        }

    }

    void Explorer::traverseMaze(Maze& maze, int x, int y, std::promise<bool>& returnValue, bool* done){

        std::promise<bool> leftPromise;
        std::future<bool> leftFuture = leftPromise.get_future();
        std::promise<bool> rightPromise;
        std::future<bool> rightFuture = rightPromise.get_future();
        std::promise<bool> upPromise;
        std::future<bool> upFuture = upPromise.get_future();
        std::promise<bool> downPromise;
        std::future<bool> downFuture = downPromise.get_future();

        std::vector<int> currentPosition = {x, y};
        std::vector<int> nextPosition = {x, y};
        std::vector<std::thread> threadList;
        bool foundEnd = false;
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;

        if (*done){
            returnValue.set_value(false);
            return;
        }

        if (x == maze.layout[y].size()-1){
            maze.layout[y][x] = "\033[32m" + maze.layout[y][x] + "\033[0m";
            returnValue.set_value(true);
            *done = true;
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        nextPosition = moveDown(maze, currentPosition[0], currentPosition[1]);
        if (currentPosition != nextPosition){
            std::thread downThread(&Explorer::traverseMaze, this, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(downPromise), done);
            threadList.push_back(std::move(downThread));
            nextPosition = currentPosition;
            down = true;
        }

        nextPosition = moveUp(maze, currentPosition[0], currentPosition[1]);
        if (currentPosition != nextPosition){
            std::thread upThread(&Explorer::traverseMaze, this, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(upPromise), done);
            threadList.push_back(std::move(upThread));
            nextPosition = currentPosition;
            up = true;
        }

        nextPosition = moveLeft(maze, currentPosition[0], currentPosition[1]);
        if (currentPosition != nextPosition){
            std::thread leftThread(&Explorer::traverseMaze, this, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(leftPromise), done);
            threadList.push_back(std::move(leftThread));
            nextPosition = currentPosition;
            left = true;
        }

        nextPosition = moveRight(maze, currentPosition[0], currentPosition[1]);
        if (currentPosition != nextPosition){
            std::thread rightThread(&Explorer::traverseMaze, this, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(rightPromise), done);
            threadList.push_back(std::move(rightThread));
            right = true;

        }

        if (threadList.size() == 0){
            returnValue.set_value(false);
            return;
        }

        if (right && rightFuture.get()){
            maze.layout[y][x] = "\033[32m" + maze.layout[y][x] + "\033[0m";
            foundEnd = true;
        }
        if (left && leftFuture.get()){
            maze.layout[y][x] = "\033[32m" + maze.layout[y][x] + "\033[0m";
            foundEnd = true;
        }
        if (up && upFuture.get()){
            maze.layout[y][x] = "\033[32m" + maze.layout[y][x] + "\033[0m";
            foundEnd = true;
        }
        if (down && downFuture.get()){
            maze.layout[y][x] = "\033[32m" + maze.layout[y][x] + "\033[0m";
            foundEnd = true;
        }
        for (int i=0; i<threadList.size(); i++){
            threadList[i].join();
        }
        if (foundEnd){
            returnValue.set_value(true);
        }
        else{
            returnValue.set_value(false);
        }
    
    }