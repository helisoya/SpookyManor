#ifndef MONSTERONE_H
#define MONSTERONE_H
#include <iostream>
#include <SpriteComponent.h>

class ManorManager;
class MonsterOne
{
    public:
        ManorManager* manager;
        SpriteComponent sprite;
        int SpawnAfterFrame;

        MonsterOne();
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

#endif // MONSTERONE_H
