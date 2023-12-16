#include "MonsterThree.h"
#include <SFML/Graphics.hpp>
#include <ManorManager.h>
#include <Player.h>

MonsterThree::MonsterThree()
{
    movX = 0;
    movY = 0;
    speed = 10;
    SpawnAfterFrame = -1;
    std::string p[] = {"front","back","left","right"} ;
    for(std::string position : p){
        texs[position].loadFromFile("assets/Monster03/"+position+".png");
    }
    sprite.sprite.setTexture(texs["front"]);
}


void MonsterThree::SetPosition(std::vector<int> pos){
    sprite.X = pos.at(0);
    sprite.Y = pos.at(1)-100;
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

    if(sprite.X - 30 < manager->player->sprite.X + 25 && manager->player->sprite.X + 25 < sprite.X + 90
       && sprite.Y +70 < manager->player->sprite.Y + 125 && manager->player->sprite.Y + 125 < sprite.Y + 170) {
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
