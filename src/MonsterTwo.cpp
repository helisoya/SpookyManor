#include "MonsterTwo.h"
#include <SFML/Graphics.hpp>
#include <SpriteComponent.h>
#include <ManorManager.h>
#include <iostream>
#include <Monster.h>

MonsterTwo::MonsterTwo()
{
    currFrame = 0;
    AnimationSpeed = 13;
    frameToNext = AnimationSpeed;
    sprite.X = 400;
    sprite.Y = 400;
    sprite.sprite.setPosition(400,400);
    for(int i = 0;i<18;i++){
        texs[i].loadFromFile("assets/Monster02/"+std::to_string(i)+".png");
    }
    Reset();
}

void MonsterTwo::MonsterLogic(){

    if(currFrame<18) {
        if(frameToNext > 0) {
            frameToNext--;
        }else {
            frameToNext = AnimationSpeed;
            currFrame++;
        }
    }else {
        std::cout << "Killed by Monster 2" << std::endl;
        manager->PlaySound(&(manager->sfx_static));
        manager->inGame = 2;
    }

    if(sprite.sprite.getTexture() != &texs[currFrame]){
        sprite.sprite.setTexture(texs[currFrame]);
    }
}

void MonsterTwo::Reset(){
    currFrame = 0;
    frameToNext = AnimationSpeed;
    sprite.sprite.setTexture(texs[0]);
}
