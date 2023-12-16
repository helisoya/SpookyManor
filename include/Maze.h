#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include <MazeTile.h>


class Maze
{
    public:
        int sizeOfMaze;
        std::vector<std::vector<MazeTile>> maze;
        Maze();
        void Reset();
        void GenerateMaze();
        bool isTileEmpty(int X,int Y);
        bool isTileExit(int X,int Y);

        MazeTile* GetTile(int X, int Y);

    protected:

    private:
};

#endif // MAZE_H
