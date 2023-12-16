#include "MazeTile.h"
#include <SFML/Graphics.hpp>

MazeTile::MazeTile(int X,int Y,int SIZE)
{
    x = X;
    y = Y;
    val = 1;
    discovered = false;
    map_shape.setPosition(x*SIZE+x*5,y*SIZE+y*5);
    map_shape.setSize(sf::Vector2f(35,35));
    map_shape.setFillColor(sf::Color(0,0,0));
}
