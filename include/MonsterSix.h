#ifndef MONSTERSIX_H
#define MONSTERSIX_H
#include <iostream>
#include <SpriteComponent.h>

class ManorManager;

class MonsterSix
{
    public:
        ManorManager* manager;
        SpriteComponent sprite;
        int SpawnAfterFrame;

        MonsterSix();
        void SetPosition(std::vector<int> pos);
        void Update();

    protected:

    private:
        int movX;
        int movY;
        int currFrame;
        int AnimationSpeed;
        int frameToNext;
        int speed;
        std::string position;
        std::map<std::string,sf::Texture[2]> texs;
};

#endif // MONSTERSIX_H
