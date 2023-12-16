#ifndef MONSTERTHREE_H
#define MONSTERTHREE_H
#include <SFML/Graphics.hpp>
#include <SpriteComponent.h>
#include <iostream>

class ManorManager;
class MonsterThree
{
    public:
        ManorManager* manager;
        SpriteComponent sprite;
        MonsterThree();

        int SpawnAfterFrame;

        int movX;
        int movY;
        std::string position;

        void SetPosition(std::vector<int> pos);
        void Update();

    protected:

    private:
        int speed;
        std::map<std::string,sf::Texture> texs;
};

#endif // MONSTERTHREE_H
