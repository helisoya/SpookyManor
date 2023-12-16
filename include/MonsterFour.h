#ifndef MONSTERFOUR_H
#define MONSTERFOUR_H
#include <SpriteComponent.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class ManorManager;

class MonsterFour
{
    public:
        ManorManager* manager;

        SpriteComponent sprite;
        int SpawnAfterFrame;

        MonsterFour();

        std::vector<int> exit;

        void SetPosition(std::vector<int> pos);
        void Update();
        void Reset();

    protected:

    private:
        int movX;
        int movY;
        int currFrame;
        int AnimationSpeed;
        int frameToNext;
        int speed;
        int speeds[2];
        int status;
        int WaitForFrame;
        std::string position;
        std::map<std::string,sf::Texture> texs_idle;
        std::map<std::string,sf::Texture[2]> texs_walk;
};

#endif // MONSTERFOUR_H
