#include "MonsterThree.h"
#include <SFML/Graphics.hpp>
#include <ManorManager.h>
#include <Player.h>
#include <Monster.h>

MonsterThree::MonsterThree()
{
    movX = 0;
    movY = 0;
    speed = 10;
    SpawnAfterFrame = -1;
    startSFX.loadFromFile("assets/Audio/m03.wav");
    std::string p[] = {"front","back","left","right"} ;
    for(std::string position : p){
        texs[position].loadFromFile("assets/Monster03/"+position+".png");
    }
    sprite.sprite.setTexture(texs["front"]);
}

void MonsterThree::ChangeMovement(int x, int y,std::string pos){
    movX = x;
    movY = y;
    position = pos;
}

void MonsterThree::Update(){
    if(manager->inGame!=1 || (sf::Keyboard::isKeyPressed(sf::Keyboard::M) || (manager->isUsingJoystick && sf::Joystick::isButtonPressed(0,0)))){
        return;
    }

    if(SpawnAfterFrame>0) {
        SpawnAfterFrame--;
    }else if(SpawnAfterFrame != -1) {
        SpawnAfterFrame = -1;
        sprite.drawable = true;
        sprite.sprite.setTexture(texs[position]);
    }


    if(!sprite.drawable) {
        return;
    }

    MonsterLogic();
}



void MonsterThree::MonsterLogic(){

    if(sprite.X - 30 < manager->player->sprite.X + 25 && manager->player->sprite.X + 25 < sprite.X + 90
       && sprite.Y +70 < manager->player->sprite.Y + 125 && manager->player->sprite.Y + 125 < sprite.Y + 170) {
        std::cout << "Killed by Monster 3" << std::endl;
        manager->inGame = 2;
        manager->PlaySound(&(manager->sfx_static));
    }


    sprite.X += movX * speed;
    sprite.Y += movY * speed;

    if((sprite.X < 0 && sprite.X+50 < 0) || sprite.X > 800 || (sprite.Y < 0 && sprite.Y+120 < 0) || sprite.Y > 800) {
        sprite.drawable = false;
    }else{
        sprite.sprite.setPosition(sprite.X,sprite.Y);
    }
}


void MonsterThree::Init(std::vector<int> position,std::string side,std::vector<int> exitPosition){
    Monster::Init(position,side,exitPosition);
    SetPosition(position);
    SpawnAfterFrame = 40;

    int x;
    int y;

    if(side.compare("left") == 0){
        x = -1;
        y = 0;
    }else if(side.compare("right") == 0){
        x = 1;
        y = 0;
    }else if(side.compare("back") == 0){
        x = 0;
        y = -1;
    }else{
        x = 0;
        y = 1;
    }

    ChangeMovement(x,y,side);
}
