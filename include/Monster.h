#ifndef MONSTER_H
#define MONSTER_H

#include "SpriteComponent.h"
#include "ManorManager.h"


class Monster
{
    public:
        SpriteComponent sprite;
        ManorManager* manager;

        int SpawnAfterFrame;

        Monster();
        virtual void Update();
        virtual void SetPosition(std::vector<int> pos);
        virtual void Init(std::vector<int> position,std::string side,std::vector<int> exitPosition);

    protected:
        int movX;
        int movY;
        int speed;
        sf::SoundBuffer startSFX;

        virtual void MonsterLogic();
};

#endif // MONSTER_H
