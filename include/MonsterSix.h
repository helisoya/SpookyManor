#ifndef MONSTERSIX_H
#define MONSTERSIX_H
#include <iostream>
#include <SpriteComponent.h>
#include <Monster.h>

class ManorManager;

class MonsterSix : public Monster
{
    public:

        MonsterSix();
        void Update();

    protected:
        void MonsterLogic();

    private:
        int currFrame;
        int AnimationSpeed;
        int frameToNext;
        std::string position;
        std::map<std::string,sf::Texture[2]> texs;
};

#endif // MONSTERSIX_H
