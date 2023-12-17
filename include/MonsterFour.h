#ifndef MONSTERFOUR_H
#define MONSTERFOUR_H
#include <SpriteComponent.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Monster.h>

class ManorManager;

class MonsterFour : public Monster
{
    public:

        MonsterFour();

        std::vector<int> exit;

        void Reset();
        void Update();

    protected:

        void MonsterLogic();

    private:

        int currFrame;
        int AnimationSpeed;
        int frameToNext;

        int speeds[2];
        int status;
        int WaitForFrame;
        std::string position;
        std::map<std::string,sf::Texture> texs_idle;
        std::map<std::string,sf::Texture[2]> texs_walk;
};

#endif // MONSTERFOUR_H
