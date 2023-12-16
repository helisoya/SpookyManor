#include "MonsterFour.h"
#include <ManorManager.h>
#include <SpriteComponent.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>

MonsterFour::MonsterFour()
{
    sprite.drawable = false;
    SpawnAfterFrame = -1;
    speeds[0] = 1;
    speeds[1] = 4;
    speed = speeds[0];

    position ="front";
    movX = 0;
    movY = 0;
    currFrame = 0;
    AnimationSpeed = 15;
    frameToNext = AnimationSpeed;

    status = 0;
    WaitForFrame = 60;

    std::string p[] = {"front","back","left","right"} ;
    for(std::string position : p){
        texs_idle[position].loadFromFile("assets/Monster04/"+position+"_idle.png");
        texs_walk[position][0].loadFromFile("assets/Monster04/"+position+"_walk_01.png");
        texs_walk[position][1].loadFromFile("assets/Monster04/"+position+"_walk_02.png");
    }
    sprite.sprite.setTexture(texs_idle["front"]);
}

void MonsterFour::Update(){
    if(manager->inGame!=1 || (sf::Keyboard::isKeyPressed(sf::Keyboard::M) || (manager->isUsingJoystick && sf::Joystick::isButtonPressed(0,0)))){
        return;
    }

    if(SpawnAfterFrame>0) {
        SpawnAfterFrame--;
    }else if(SpawnAfterFrame != -1) {
        SpawnAfterFrame = -1;
        sprite.drawable = true;
    }


    if(!sprite.drawable) {
        return;
    }

    if(frameToNext > 0) {
        frameToNext--;
    }else {
        frameToNext = AnimationSpeed;

        currFrame++;
        if(currFrame>1) {
            currFrame = 0;
        }
    }
    if(manager->player->isWalking() && status !=5){
        speed = speeds[1];
        status = 5;
        return;
    }

    if(sprite.X - 30 < manager->player->sprite.X + 25 && manager->player->sprite.X + 25 < sprite.X + 90
       && sprite.Y +100 < manager->player->sprite.Y + 125 && manager->player->sprite.Y + 125 < sprite.Y + 200) {
        manager->inGame = 2;
        manager->PlaySound(&(manager->sfx_static));
    }

    if(sprite.X+60 < 0 ||sprite.X>800 || sprite.Y+150<0 ||sprite.Y>800){
        sprite.drawable = false;
    }

    switch(status){
        case 0:
            exit.at(1)-=100;
            movX = 0;
            movY = 0;
            if(sprite.X==50){
                movX = 1;
                position = "right";
            }else if(sprite.X== 750){
                movX = -1;
                position = "left";
            }
            if(sprite.Y==-50){
                movY = 1;
                position = "front";
            }else if(sprite.Y==650){
                movY = -1;
                position = "back";
            }

            sprite.sprite.setPosition(sprite.X,sprite.Y);
            sprite.sprite.setTexture(texs_walk[position][currFrame]);
            status++;
            break;
        case 1:
            if(sprite.X==400 && sprite.Y==400){
                status++;
                sprite.sprite.setTexture(texs_idle[position]);
            }else{
                sprite.X+=speed*movX;
                sprite.Y+=speed*movY;
                sprite.sprite.setPosition(sprite.X,sprite.Y);
                sprite.sprite.setTexture(texs_walk[position][currFrame]);
            }
            break;
        case 2:
            if(WaitForFrame>0){
                WaitForFrame--;
            }else{
                status++;
            }
            break;
        case 3:
            movX = 0;
            movY = 0;
            if(exit.at(0)==50){
                movX = -1;
                position = "left";
            }else if(exit.at(0)== 750){
                movX = 1;
                position = "right";
            }
            if(exit.at(1)==-50){
                movY = -1;
                position = "back";
            }else if(exit.at(1)==650){
                movY = 1;
                position = "front";
            }
            sprite.sprite.setTexture(texs_idle[position]);
            status++;
            break;
        case 4:
            sprite.X+=speed*movX;
            sprite.Y+=speed*movY;
            sprite.sprite.setPosition(sprite.X,sprite.Y);
            sprite.sprite.setTexture(texs_walk[position][currFrame]);
            break;
        case 5:
            if((sprite.X - 10 ) < manager->player->sprite.X && manager->player->sprite.X < ( sprite.X + 10)) {
                movX = 0;
            }else {
                movX = manager->player->sprite.X > sprite.X ? 1:-1 ;
                if(movX < 0) {
                    position = "left";
                }else if(movX > 0) {
                    position = "right";
                }
            }

            if((sprite.Y + 140 ) < manager->player->sprite.Y+120 && manager->player->sprite.Y+120 < ( sprite.Y + 160)) {
                movY = 0;
            }else {
                movY = manager->player->sprite.Y > sprite.Y ? 1:-1 ;
                if(movY > 0) {
                    position = "front";
                }else if(movY < 0) {
                    position = "back";
                }
            }
            if(!manager->CheckIfTouch(sprite.X+movX*speed, sprite.Y+120,60,50)) {
                sprite.X += movX * speed;
            }
            if(!manager->CheckIfTouch(sprite.X, sprite.Y+movY*speed+120,60,50)) {
                sprite.Y += movY * speed;
            }
            sprite.sprite.setPosition(sprite.X,sprite.Y);
            sprite.sprite.setTexture(texs_walk[position][currFrame]);
    }

}


void MonsterFour::SetPosition(std::vector<int> pos){
    sprite.X = pos.at(0);
    sprite.Y = pos.at(1)-100;
}

void MonsterFour::Reset(){
    status = 0;
    speed = speeds[0];
    WaitForFrame = 60;
}
