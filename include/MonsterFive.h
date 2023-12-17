#ifndef MONSTERFIVE_H
#define MONSTERFIVE_H
#include <iostream>
#include <SpriteComponent.h>
#include <Monster.h>

class ManorManager;

class MonsterFive : public Monster
{
    public:

        MonsterFive();

    protected:
        void MonsterLogic();

    private:
        std::string position;
        std::map<std::string,sf::Texture> texs;
};

#endif // MONSTERFIVE_H
