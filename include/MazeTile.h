#ifndef MAZETILE_H
#define MAZETILE_H
#include <SFML/Graphics.hpp>


class MazeTile
{
    public:
        MazeTile(int X,int Y,int SIZE);
        int x;
        int y;
        int val;
        bool discovered;
        sf::RectangleShape map_shape;

    protected:

    private:
};

#endif // MAZETILE_H
