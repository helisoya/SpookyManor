#ifndef MANORMANAGER_H
#define MANORMANAGER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Rectangle.h>
#include <Maze.h>
#include <vector>
#include <MiniMap.h>
#include <SFML/Audio.hpp>

class MonsterOne;
class MonsterTwo;
class MonsterThree;
class MonsterFour;
class MonsterFive;
class MonsterSix;
class Player;

class ManorManager
{
    public:
        Player* player;
        MonsterOne* m_01;
        MonsterTwo* m_02;
        MonsterThree* m_03;
        MonsterFour* m_04;
        MonsterFive* m_05;
        MonsterSix* m_06;

        MiniMap* minimap;

        Maze maze;

        sf::Color color_floor;

        sf::Color minimap_bg;
        sf::Color minimap_discovered;
        sf::Color minimap_notdiscovered;
        sf::Color minimap_player;
        sf::Color minimap_exit;

        sf::SoundBuffer sfx_static;
        sf::SoundBuffer sfx_m01;
        sf::SoundBuffer sfx_m02;
        sf::SoundBuffer sfx_m03;
        sf::SoundBuffer sfx_m04;
        sf::SoundBuffer sfx_m05;
        sf::SoundBuffer sfx_m06;

        sf::Sound sound;

        bool isUsingJoystick;


        int inGame;

        std::vector<Rectangle*> walls;

        std::vector<int> start_middle;
        std::vector<int> start_left;
        std::vector<int> start_right;
        std::vector<int> start_up;
        std::vector<int> start_down;

        ManorManager();

        bool CheckIfTouch(int X,int Y,int WIDTH, int HEIGHT);

        int sizeOfMaze;

        int posX;
        int posY;

        int startX;
        int startY;

        void LoadRoom(int X,int Y);

        void Reset();

        void PlaySound(sf::SoundBuffer* buffer);

    protected:

    private:
        void UpdateMinimap();
        sf::Color getColorOfTile(int X,int Y);
};

#endif // MANORMANAGER_H
