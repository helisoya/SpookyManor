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
        void Init(std::vector<int> position,std::string side,std::vector<int> exitPosition);

    protected:
        void MonsterLogic();

    private:
        std::string position;
        std::map<std::string,sf::Texture> texs;
};

#endif // MONSTERTHREE_H
