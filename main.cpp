#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>

void showMaze(std::vector<std::vector<std::string> >&maze, bool foundEnd){

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

    if (x > 1 && isOpen(std::ref(maze), x-1, y)){

       maze[y][x-1] = "\u2190"; 
       return {x-1, y};
    }
    else{
        return {x, y};
    }

}

std::vector<int> moveRight(std::vector<std::vector<std::string> >&maze, int x, int y){

    if (x < maze[y].size() && isOpen(std::ref(maze), x+1, y)){
        
       maze[y][x+1] = "\u2192"; 
       return {x+1, y};
    }
    else{
        return {x, y};
    }

}

std::vector<int> moveDown(std::vector<std::vector<std::string> >&maze, int x, int y){
 
    if (y < maze.size() && isOpen(std::ref(maze), x, y+1)){

       maze[y+1][x] = "\u2193"; 
       return {x, y+1};
    }
    else{
        return {x, y};
    }

}

std::vector<int> moveUp(std::vector<std::vector<std::string> >&maze, int x, int y){

    if (y > 1 && isOpen(std::ref(maze), x, y-1)){

       maze[y-1][x] = "\u2191"; 
       return {x, y-1};
    }
    else{
        return {x, y};
    }

}

void traverseMaze(std::vector<std::vector<std::string> >& maze, int x, int y, std::promise<bool>& returnValue){

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

    if (x == maze[y].size()-1){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        returnValue.set_value(true);
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    nextPosition = moveDown(std::ref(maze), currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        std::thread downThread(traverseMaze, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(downPromise));
        threadList.push_back(std::move(downThread));
        nextPosition = currentPosition;
        down = true;
    }

    nextPosition = moveUp(std::ref(maze), currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        std::thread upThread(traverseMaze, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(upPromise));
        threadList.push_back(std::move(upThread));
        nextPosition = currentPosition;
        up = true;
    }

    nextPosition = moveLeft(std::ref(maze), currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        std::thread leftThread(traverseMaze, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(leftPromise));
        threadList.push_back(std::move(leftThread));
        nextPosition = currentPosition;
        left = true;
    }

    nextPosition = moveRight(std::ref(maze), currentPosition[0], currentPosition[1]);
    if (currentPosition != nextPosition){
        std::thread rightThread(traverseMaze, std::ref(maze), nextPosition[0], nextPosition[1], std::ref(rightPromise));
        threadList.push_back(std::move(rightThread));
        right = true;

    }

    if (threadList.size() == 0){
        returnValue.set_value(false);
        return;
    }

    if (right && rightFuture.get()){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(std::ref(maze), true);
        returnValue.set_value(true);
    }
    if (left && leftFuture.get()){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(std::ref(maze), true);
        returnValue.set_value(true);
    }
    if (up && upFuture.get()){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(std::ref(maze), true);
        returnValue.set_value(true);
    }
    if (down && downFuture.get()){
        maze[y][x] = "\033[32m" + maze[y][x] + "\033[0m";
        showMaze(std::ref(maze), true);
        returnValue.set_value(true);
    }
    for (int i=0; i<threadList.size(); i++){
        threadList[i].join();
    }


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
    std::promise<bool> foundEnd;
    std::future<bool> foundEndFuture = foundEnd.get_future();
    
    std::thread initThread(traverseMaze, std::ref(maze), currentPosition[0], currentPosition[1], std::ref(foundEnd));

    while (foundEndFuture.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
        showMaze(maze, false);
    }
    showMaze(maze, true);
    
    initThread.join();



}
