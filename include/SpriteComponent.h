#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SFML/Graphics.hpp>

class SpriteComponent
{
    public:
        int X;
        int Y;
        sf::Sprite sprite;
        bool drawable;

        SpriteComponent();
        bool operator< (const SpriteComponent &other) const{
            return Y < other.Y;
        }
        bool operator> (const SpriteComponent &other) const{
            return Y < other.Y;
        }

    protected:

    private:
};


#endif // SPRITECOMPONENT_H
