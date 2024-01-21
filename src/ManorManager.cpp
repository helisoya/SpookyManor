#include "ManorManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Rectangle.h>
#include <Maze.h>
#include <vector>
#include <MiniMap.h>
#include <MonsterOne.h>
#include <MonsterTwo.h>
#include <MonsterThree.h>
#include <MonsterFour.h>
#include <MonsterFive.h>
#include <MonsterSix.h>

ManorManager::ManorManager()
{
    sizeOfMaze = 20;

    isUsingJoystick = false;

    posX = 0;
    posY = 0;
    startX = 0;
    startY = 0;

    color_floor = sf::Color(150,10,10);
    minimap_bg = sf::Color(0,0,0);
    minimap_discovered = sf::Color(0,100,0);
    minimap_notdiscovered = sf::Color(100,100,100);
    minimap_player = sf::Color(200,200,200);
    minimap_exit = sf::Color(0,0,100);

    inGame = 0;

    start_middle = {400,400};
    start_left = {50,350};
    start_right = {750,350};
    start_up = {400,50};
    start_down = {400,720};

    sfx_static.loadFromFile("assets/Audio/static.wav");

    walls.push_back(new Rectangle(250,0,300,100)); // PORTE NORD - 0
    walls.push_back(new Rectangle(250,700,300,100)); // PORTE SUD - 1
    walls.push_back(new Rectangle(0,250,100,300)); // PORTE OUEST - 2
    walls.push_back(new Rectangle(700,250,100,300)); // PORTE EST - 3
    walls.at(0)->drawable = false;
    walls.at(1)->drawable = false;
    walls.at(2)->drawable = false;
    walls.at(3)->drawable = false;

    walls.push_back(new Rectangle(0,0,250,100));
    walls.push_back(new Rectangle(0,0,100,250));

    walls.push_back(new Rectangle(550,0,250,100));
    walls.push_back(new Rectangle(700,0,100,250));

    walls.push_back(new Rectangle(0,550,100,250));
    walls.push_back(new Rectangle(0,700,250,100));

    walls.push_back(new Rectangle(550,700,250,100));
    walls.push_back(new Rectangle(700,550,100,250));

}
void ManorManager::PlaySound(sf::SoundBuffer* buffer){
    sound.stop();
    sound.setBuffer(*buffer);
    sound.setVolume(50);
    sound.play();

}

bool ManorManager::CheckIfTouch(int X,int Y,int WIDTH,int HEIGHT){
    for(Rectangle* rec : walls){
        if(rec->drawable){
            if(rec->CheckIfTouch(X,Y,WIDTH,HEIGHT)){
                return true;
            }
        }

    }
    return false;
}

void ManorManager::LoadRoom(int X,int Y){
    sound.stop();
    maze.GetTile(posX,posY)->map_shape.setFillColor(minimap_discovered);
    posX += X;
    posY += Y;
    maze.GetTile(posX,posY)->map_shape.setFillColor(minimap_player);

    if(!maze.GetTile(posX,posY)->discovered){
        maze.GetTile(posX,posY)->discovered = true;
    }
    if(maze.isTileExit(posX,posY)){
        inGame = 3;
        return;
    }
    walls.at(0)->drawable = true;
    walls.at(1)->drawable = true;
    walls.at(2)->drawable = true;
    walls.at(3)->drawable = true;

    std::vector<std::vector<int>> possibilities;

    if(posX > 0) { // PORTE OUEST
        if(maze.isTileEmpty(posX-1, posY)) {
            walls.at(2)->drawable = false;
            possibilities.push_back(start_left);
            if(!maze.GetTile(posX-1,posY)->discovered){
                if(maze.isTileExit(posX-1,posY)){
                    maze.GetTile(posX-1,posY)->map_shape.setFillColor(minimap_exit);
                }else{
                    maze.GetTile(posX-1,posY)->map_shape.setFillColor(minimap_notdiscovered);
                }
            }
        }
    }
    if(posY > 0) { // PORTE NORD

        if(maze.isTileEmpty(posX, posY-1)) {
            walls.at(0)->drawable = false;
            possibilities.push_back(start_up);
            if(!maze.GetTile(posX,posY-1)->discovered){
                if(maze.isTileExit(posX,posY-1)){
                    maze.GetTile(posX,posY-1)->map_shape.setFillColor(minimap_exit);
                }else{
                    maze.GetTile(posX,posY-1)->map_shape.setFillColor(minimap_notdiscovered);
                }
            }
        }
    }
    if(posX < sizeOfMaze-1) { // PORTE EST
        if(maze.isTileEmpty(posX+1, posY)) {
            walls.at(3)->drawable = false;
            possibilities.push_back(start_right);
            if(!maze.GetTile(posX+1,posY)->discovered){
                if(maze.isTileExit(posX+1,posY)){
                    maze.GetTile(posX+1,posY)->map_shape.setFillColor(minimap_exit);
                }else{
                    maze.GetTile(posX+1,posY)->map_shape.setFillColor(minimap_notdiscovered);
                }

            }
        }
    }
    if(posY < sizeOfMaze-1) { // PORTE SUD
        if(maze.isTileEmpty(posX, posY+1)) {
            walls.at(1)->drawable = false;
            possibilities.push_back(start_down);
            if(!maze.GetTile(posX,posY+1)->discovered){
                if(maze.isTileExit(posX,posY+1)){
                    maze.GetTile(posX,posY+1)->map_shape.setFillColor(minimap_exit);
                }else{
                    maze.GetTile(posX,posY+1)->map_shape.setFillColor(minimap_notdiscovered);
                }
            }
        }
    }

    UpdateMinimap();

    for(int i = 0;i < monsters->size();i++){
        monsters->at(i)->SpawnAfterFrame = -1;
        monsters->at(i)->sprite.drawable = false;
    }

    if(posX == startX && posY == startY){
        return;
    }

    if(rand() % 6 <= 2){
        int chosenIndex = rand() % monsters->size();
        Monster* chosenMonster = monsters->at(chosenIndex);

        int nbPossibilities = possibilities.size();
        std::vector<int> start = possibilities.at(rand() % nbPossibilities);
        std::vector<int> exit = possibilities.at(rand() % nbPossibilities);
        std::string side;
        if(start==start_left){
            side = "right";
        }
        else if(start==start_right){
            side = "left";
        }
        else if(start==start_down){
            side = "back";
        }
        else{
            side = "front";
        }

        chosenMonster->Init(start,side,exit);
        return;
    }

    /*
    if(rand() % 100 <= 20){ // Monstre 1 - Zombie Blanc
        PlaySound(&sfx_m01);
        m_01->SpawnAfterFrame = 40;
        m_01->SetPosition(possibilities.at(rand() % possibilities.size()));
        return;
    }
    if(rand() % 100 <= 20){ // Monstre 2 - Bombe
        m_02->Reset();
        PlaySound(&sfx_m02);
        m_02->sprite.drawable = true;
        return;
    }
    if(rand() % 100 <= 20){ // Monstre 3 - Purple HoverBoard
        m_03->SpawnAfterFrame = 40;
        PlaySound(&sfx_m03);
        int c = rand() % possibilities.size();
        m_03->SetPosition(possibilities.at(c));
        if(possibilities.at(c)==start_left){
            m_03->ChangeMovement(1,0,"right");
        }
        else if(possibilities.at(c)==start_right){
            m_03->ChangeMovement(-1,0,"left");
        }
        else if(possibilities.at(c)==start_down){
            m_03->ChangeMovement(0,-1,"back");
        }
        else if(possibilities.at(c)==start_up){
            m_03->ChangeMovement(0,1,"front");
        }
        return;
    }
    if(rand() % 100 <= 20){ // Monstre 4 - Monstre Aveugle
        PlaySound(&sfx_m04);
        m_04->Reset();
        m_04->SpawnAfterFrame = 120;
        m_04->SetPosition(possibilities.at(rand() % possibilities.size()));
        m_04->exit = possibilities.at(rand() % possibilities.size());
        return;
    }
    if(rand() % 100 <= 30){ // Monstre 5 - L'Ombre
        PlaySound(&sfx_m05);
        m_05->SpawnAfterFrame = 40;
        m_05->SetPosition(possibilities.at(rand() % possibilities.size()));
        return;
    }
    if(rand() % 100 <= 3){ // Monstre 6 - Harold
        PlaySound(&sfx_m06);
        m_06->SpawnAfterFrame = 50;
        m_06->SetPosition(possibilities.at(rand() % possibilities.size()));
        return;
    }*/

}

void ManorManager::UpdateMinimap(){
    if(posX > 0 && posY > 0){ // Haut Gauche
        minimap->shapes[1].setFillColor(getColorOfTile(posX-1,posY-1));
    }else{
        minimap->shapes[1].setFillColor(minimap_bg);
    }
    if(posY > 0){ // Haut
        minimap->shapes[2].setFillColor(getColorOfTile(posX,posY-1));
    }else{
        minimap->shapes[2].setFillColor(minimap_bg);
    }
    if(posX < sizeOfMaze-1 && posY > 0){ // Haut Droite
        minimap->shapes[3].setFillColor(getColorOfTile(posX+1,posY-1));
    }else{
        minimap->shapes[3].setFillColor(minimap_bg);
    }

    if(posX > 0){ // Centre Gauche
        minimap->shapes[4].setFillColor(getColorOfTile(posX-1,posY));
    }else{
        minimap->shapes[4].setFillColor(minimap_bg);
    }
    if(posX < sizeOfMaze-1){ // Centre Droite
        minimap->shapes[6].setFillColor(getColorOfTile(posX+1,posY));
    }else{
        minimap->shapes[6].setFillColor(minimap_bg);
    }

    if(posX > 0 && posY < sizeOfMaze-1){ // Bas Gauche
        minimap->shapes[7].setFillColor(getColorOfTile(posX-1,posY+1));
    }else{
        minimap->shapes[7].setFillColor(minimap_bg);
    }
    if(posY < sizeOfMaze-1){ // Bas
        minimap->shapes[8].setFillColor(getColorOfTile(posX,posY+1));
    }else{
        minimap->shapes[8].setFillColor(minimap_bg);
    }
    if(posX < sizeOfMaze-1 && posY < sizeOfMaze-1){ // Bas Droite
        minimap->shapes[9].setFillColor(getColorOfTile(posX+1,posY+1));
    }else{
        minimap->shapes[9].setFillColor(minimap_bg);
    }

}

sf::Color ManorManager::getColorOfTile(int X,int Y){
    if(maze.GetTile(X,Y)->val==1){
        return minimap_bg;
    }
    if(maze.GetTile(X,Y)->discovered){
        return minimap_discovered;
    }
    if(maze.isTileExit(X,Y)){
        return minimap_exit;
    }
    return minimap_notdiscovered;
}

void ManorManager::Reset(){
    maze.GenerateMaze();
    posX = rand() % sizeOfMaze ;
    posY = rand() % sizeOfMaze ;
    while(!maze.isTileEmpty(posX,posY) || maze.isTileExit(posX,posY)){
        posX = rand() % sizeOfMaze ;
        posY = rand() % sizeOfMaze ;
    }

    startX = posX;
    startY = posY;
    LoadRoom(0,0);
}
