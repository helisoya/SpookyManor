#ifndef MONSTERTWO_H
#define MONSTERTWO_H
#include <SpriteComponent.h>
#include <SFML/Graphics.hpp>

class ManorManager;

class MonsterTwo
{
    public:
        SpriteComponent sprite;
        ManorManager* manager;
        MonsterTwo();

        void Update();
        void Reset();

    protected:

    private:
        int currFrame;
        int AnimationSpeed;
        int frameToNext;
        sf::Texture texs[18];
};

#endif // MONSTERTWO_H
