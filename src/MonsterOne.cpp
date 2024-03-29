#include "MonsterOne.h"
#include <ManorManager.h>
#include <SpriteComponent.h>
#include <iostream>
#include <Player.h>
#include <Monster.h>

MonsterOne::MonsterOne()
{
    sprite.drawable = false;
    movX = 0;
    movY = 0;
    currFrame = 0;
    AnimationSpeed = 30;
    frameToNext = AnimationSpeed;
    speed = 1;
    SpawnAfterFrame = -1;
    position = "front";
    startSFX.loadFromFile("assets/Audio/m01.wav");

    std::string p[] = {"front","back","left","right"} ;
    for(std::string position : p){
        texs[position][0].loadFromFile("assets/Monster01/"+position+"_01.png");
        texs[position][1].loadFromFile("assets/Monster01/"+position+"_02.png");

    }
    sprite.sprite.setTexture(texs["front"][0]);
    sprite.sprite.setPosition(sprite.X,sprite.Y);

}

void MonsterOne::MonsterLogic(){

    if(frameToNext > 0) {
        frameToNext--;
    }else {
        frameToNext = AnimationSpeed;

        currFrame++;
        if(currFrame>1) {
            currFrame = 0;
        }
    }

    if(sprite.X - 30 < manager->player->sprite.X + 25 && manager->player->sprite.X + 25 < sprite.X + 90
       && sprite.Y +100 < manager->player->sprite.Y + 125 && manager->player->sprite.Y + 125 < sprite.Y + 200) {
        std::cout << "Killed by Monster 1" << std::endl;
        manager->inGame = 2;
        manager->PlaySound(&(manager->sfx_static));
    }

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
    if(sprite.sprite.getTexture() != &texs[position][currFrame]){
        sprite.sprite.setTexture(texs[position][currFrame]);
    }
}

void MonsterOne::Init(std::vector<int> position,std::string side,std::vector<int> exitPosition){
    Monster::Init(position,side,exitPosition);
    SpawnAfterFrame = 40;
    SetPosition(position);
}
