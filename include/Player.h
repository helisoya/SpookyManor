#ifndef PLAYER_H
#define PLAYER_H
#include <SpriteComponent.h>
#include <iostream>
#include <vector>

class ManorManager;

class Player
{
    public:
        ManorManager* manager;

        SpriteComponent sprite;
        Player();
        void Update();
        bool isWalking();
        void SetPosition(std::vector<int> pos);
        std::string position;

    protected:

    private:

        int movX;
        int movY;
        int currFrame;
        int animationSpeed[2];
        int frameToNext;
        int speed;
        std::map<std::string,sf::Texture[2]> tex_stand;
        std::map<std::string,sf::Texture[2]> tex_walk;
};

#endif // PLAYER_H
