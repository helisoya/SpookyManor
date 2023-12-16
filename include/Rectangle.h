#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <SFML/Graphics.hpp>

class Rectangle
{
    public:
        sf::RectangleShape shape;
        int x;
        int y;
        int width;
        int height;
        bool drawable;
        sf::Rect<int> hitbox;
        Rectangle(int X, int Y, int WIDTH, int HEIGHT);
        bool CheckIfTouch(int X, int Y, int WIDTH, int HEIGHT);

    protected:

    private:
};

#endif // RECTANGLE_H
