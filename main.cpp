#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>

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
