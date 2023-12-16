#include "Rectangle.h"
#include <SFML/Graphics.hpp>

Rectangle::Rectangle(int X, int Y, int WIDTH, int HEIGHT)
{
    x = X;
    y = Y;
    width = WIDTH;
    height = HEIGHT;
    drawable = true;
    shape.setPosition(x,y);
    shape.setSize(sf::Vector2f(width,height));
    shape.setFillColor(sf::Color(150,150,150));
    hitbox.top = Y;
    hitbox.left = X;
    hitbox.width = WIDTH;
    hitbox.height = HEIGHT;
}

bool Rectangle::CheckIfTouch(int X, int Y, int WIDTH, int HEIGHT){
    return hitbox.intersects(sf::Rect<int>(sf::Vector2i(X,Y),sf::Vector2i(WIDTH,HEIGHT)));
    //return ( x <= X && X <= x+width && y <= Y && Y <= y+height ) || ( x <= X+WIDTH && X+WIDTH <= x+width && y <= Y+HEIGHT && Y+HEIGHT <= y+height );
}
