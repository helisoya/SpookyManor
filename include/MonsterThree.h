#ifndef MONSTERTHREE_H
#define MONSTERTHREE_H

#include <SFML/Graphics.hpp>
#include <SpriteComponent.h>
#include <iostream>
#include "Monster.h"

class ManorManager;
class MonsterThree : public Monster
{
    public:
        MonsterThree();

        void ChangeMovement(int x,int y,std::string pos);
        void Update();

    protected:
        void MonsterLogic();

    private:
        std::string position;
        std::map<std::string,sf::Texture> texs;
};

#endif // MONSTERTHREE_H
