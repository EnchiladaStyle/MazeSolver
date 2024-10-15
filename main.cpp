#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>

void showMaze(std::vector<std::vector<std::string> >maze, bool foundEnd){

    std::system("clear");

    for (std::vector<std::string> level : maze){

        for (std::string cell : level){
            std::cout<<cell;
        }
        std::cout<<std::endl;

    }

    if (!foundEnd){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

}

bool isOpen(std::vector<std::vector<std::string> >&maze, int x, int y){

    if (maze[y][x] == " "){
        return true;
    }
    else{
        return false;
    }
}

std::vector<int> moveLeft(std::vector<std::vector<std::string> >&maze, int x, int y){
    
    if (x > 1 && isOpen(maze, x-1, y)){

       maze[y][x-1] = "\u2190"; 
       return {x-1, y};
    }
    else{
        return {x, y};
    }

}

std::vector<int> moveRight(std::vector<std::vector<std::string> >&maze, int x, int y){
    
    if (x < maze[y].size() && isOpen(maze, x+1, y)){

       maze[y][x+1] = "\u2192"; 
       return {x+1, y};
    }
    else{
        return {x, y};
    }

}

std::vector<int> moveDown(std::vector<std::vector<std::string> >&maze, int x, int y){
    
    if (y < maze.size() && isOpen(maze, x, y+1)){

       maze[y+1][x] = "\u2193"; 
       return {x, y+1};
    }
    else{
        return {x, y};
    }

}

std::vector<int> moveUp(std::vector<std::vector<std::string> >&maze, int x, int y){
    
    if (y > 1 && isOpen(maze, x, y-1)){

       maze[y-1][x] = "\u2191"; 
       return {x, y-1};
    }
    else{
        return {x, y};
    }

}

bool traverseMaze(std::vector<std::vector<std::string> >& maze, int x, int y){

    std::vector<int> currentPosition = {x, y};
    std::vector<int> nextPosition = {x, y};
    bool foundEnd = false;

    if (x == maze[y].size()-1){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        return true;
    }

    showMaze(maze, false);

    nextPosition = moveDown(maze, currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        foundEnd = traverseMaze(maze, nextPosition[0], nextPosition[1]);
        nextPosition = currentPosition;
    }

    if (foundEnd){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(maze, true);
        return true;
    }

    nextPosition = moveUp(maze, currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        foundEnd = traverseMaze(maze, nextPosition[0], nextPosition[1]);
        nextPosition = currentPosition;
    }

    if (foundEnd){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(maze, true);
        return true;
    }

    nextPosition = moveLeft(maze, currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        foundEnd = traverseMaze(maze, nextPosition[0], nextPosition[1]);
        nextPosition = currentPosition;
    }

    if (foundEnd){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(maze, true);
        return true;
    }

    nextPosition = moveRight(maze, currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        foundEnd = traverseMaze(maze, nextPosition[0], nextPosition[1]);
    }

    if (foundEnd){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(maze, true);
        return true;
    }

    return false;

}

int main(){

    std::vector<std::vector<std::string> > maze = {
    {"\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588"},
    {   " ",      " ",      " ",   "\u2588",    " ",      " ",      " ",      " ",      " ",   "\u2588"},
    {"\u2588", "\u2588",    " ",   "\u2588",    " ",   "\u2588",    " ",   "\u2588", "\u2588", "\u2588"},
    {"\u2588", "\u2588",    " ",      " ",      " ",   "\u2588",    " ",      " ",      " ",   "\u2588"},
    {"\u2588",    " ",      " ",   "\u2588", "\u2588", "\u2588", "\u2588",    " ",   "\u2588", "\u2588"},
    {"\u2588",    " ",   "\u2588", "\u2588", "\u2588",    " ",      " ",      " ",      " ",   "\u2588"},
    {"\u2588",    " ",   "\u2588",    " ",      " ",   "\u2588", "\u2588",    " ",   "\u2588", "\u2588"},
    {"\u2588",    " ",      " ",   "\u2588",    " ",   "\u2588", "\u2588",    " ",   "\u2588", "\u2588"},
    {"\u2588", "\u2588",    " ",      " ",      " ",   "\u2588",    " ",      " ",      " ",      " "  },
    {"\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588", "\u2588"},

};

    std::vector<int> currentPosition = {0, 1};
    
    traverseMaze(maze, currentPosition[0], currentPosition[1]);



}
