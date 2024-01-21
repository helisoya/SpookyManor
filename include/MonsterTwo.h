#ifndef MONSTERTWO_H
#define MONSTERTWO_H
#include <SpriteComponent.h>
#include <SFML/Graphics.hpp>
#include <Monster.h>

class ManorManager;

class MonsterTwo : public Monster
{
    public:
        MonsterTwo();

        void Reset();
        void Init(std::vector<int> position,std::string side,std::vector<int> exitPosition);

    protected:
        void MonsterLogic();

    private:
        int currFrame;
        int AnimationSpeed;
        int frameToNext;
        sf::Texture texs[18];
};

#endif // MONSTERTWO_H
