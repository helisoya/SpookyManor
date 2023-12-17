#ifndef MONSTERONE_H
#define MONSTERONE_H

#include <iostream>
#include <SpriteComponent.h>
#include "Monster.h"


class ManorManager;
class MonsterOne : public Monster
{
    public:

        MonsterOne();

    protected:

        void MonsterLogic();

    private:
        int currFrame;
        int AnimationSpeed;
        int frameToNext;
        std::string position;
        std::map<std::string,sf::Texture[2]> texs;


};

#endif // MONSTERONE_H
