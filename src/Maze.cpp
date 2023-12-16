#include "Maze.h"
#include <MazeTile.h>
#include <vector>
#include <cstdlib>
#include <iostream>

Maze::Maze()
{
    sizeOfMaze = 20;
    int sizeOfSquare = (800-(5*sizeOfMaze))/sizeOfMaze;

    for(int i =0;i<sizeOfMaze;i++){
        maze.push_back(std::vector<MazeTile>());
        for(int j = 0;j<sizeOfMaze;j++){
            maze.at(i).push_back(MazeTile(j,i,sizeOfSquare));
        }
    }
}
void Maze::Reset(){
    for(int i = 0;i<sizeOfMaze;i++){
        for(int j = 0;j<sizeOfMaze;j++){
            GetTile(j,i)->discovered = false;
            GetTile(j,i)->val = 1;
            GetTile(j,i)->map_shape.setFillColor(sf::Color(0,0,0));
        }
    }
}

bool Maze::isTileEmpty(int x,int y){
    return maze.at(y).at(x).val != 1;
}

bool Maze::isTileExit(int x,int y){
    return maze.at(y).at(x).val == 2;
}

MazeTile* Maze::GetTile(int X,int Y){
    return &maze.at(Y).at(X);
}


void Maze::GenerateMaze(){
    Reset();

    int maxTunnel = sizeOfMaze * 5;
    int currLength = 0;
    int randomLength = rand() % 4 + 2;

    int currX = 0;
    int currY = 0;

    std::vector<int> up = {-1,0};
    std::vector<int> down = {1,0};
    std::vector<int> left = {0,-1};
    std::vector<int> right = {0,1};

    while(maxTunnel > 0) {
        std::vector<std::vector<int>> ways;
        if (!(currX <= 0)) {
            ways.push_back(up);
        }
        if (!(currX >= sizeOfMaze-1)) {
            ways.push_back(down);
        }
        if (!(currY <= 0)) {
            ways.push_back(left);
        }
        if (!(currY >= sizeOfMaze-1)) {
            ways.push_back(right);
        }

        std::vector<int> mov = ways.at(rand() % ways.size());

        while( currLength < randomLength) {
            if (currX+mov.at(0) > sizeOfMaze-1 || currY+mov.at(1) > sizeOfMaze-1 || currX+mov.at(0) < 0 || currY+mov.at(1) < 0) {
                currLength = randomLength;
                break;
            }

            maze.at(currY).at(currX).val = 0;

            currX+= mov.at(0);
            currY+=mov.at(1);
            currLength++;
        }

        currLength = 0;
        randomLength = rand() % 4 +2;
        maxTunnel--;

    }
    maze.at(currY).at(currX).val = 2;
}
