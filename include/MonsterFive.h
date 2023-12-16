#ifndef MONSTERFIVE_H
#define MONSTERFIVE_H
#include <iostream>
#include <SpriteComponent.h>

class ManorManager;

class MonsterFive
{
    public:
        SpriteComponent sprite;
        ManorManager* manager;

        int SpawnAfterFrame;

        MonsterFive();
        void Update();
        void SetPosition(std::vector<int> pos);
    protected:

    private:
        int movX;
        int movY;
        int speed;
        std::string position;
        std::map<std::string,sf::Texture> texs;
};

#endif // MONSTERFIVE_H
