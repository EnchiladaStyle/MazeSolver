#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>

class Maze{

    public:

        std::vector<std::vector<std::string> > maze;

        Maze(std::vector<std::vector<std::string> >_maze){
            maze = _maze;
        }

        void showMaze(bool foundEnd){

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


        bool isOpen(int x, int y){

            if (maze[y][x] == " "){
                return true;
            }
            else{
                return false;
            }
}

    private:

};