#include "MonsterTwo.h"
#include <SFML/Graphics.hpp>
#include <SpriteComponent.h>
#include <ManorManager.h>
#include <iostream>

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

void MonsterTwo::Update(){
    if(manager->inGame!=1 || (sf::Keyboard::isKeyPressed(sf::Keyboard::M) || (manager->isUsingJoystick && sf::Joystick::isButtonPressed(0,0)))){
        return;
    }

    if(!sprite.drawable) {
        return;
    }

    if(currFrame<18) {
        if(frameToNext > 0) {
            frameToNext--;
        }else {
            frameToNext = AnimationSpeed;
            currFrame++;
        }
    }else {
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
