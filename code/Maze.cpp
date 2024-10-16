
#include "Maze.h"


        Maze::Maze(std::vector<std::vector<std::string> >_maze){
            layout = _maze;
        }

        void Maze::showMaze(bool foundEnd){

            std::system("clear");

            for (std::vector<std::string> level : layout){

                for (std::string cell : level){
                    std::cout<<cell;
                }
                std::cout<<std::endl;

            }

            if (!foundEnd){
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } 

        }


        bool Maze::isOpen(int x, int y){

            if (layout[y][x] == " "){
                return true;
            }
            else{
                return false;
            }
}