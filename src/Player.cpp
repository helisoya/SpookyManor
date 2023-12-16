#include "Player.h"
#include <SpriteComponent.h>
#include <SFML/Graphics.hpp>
#include <ManorManager.h>
#include <vector>

Player::Player()
{
    movX = 0;
    movY = 0;
    currFrame = 0;
    animationSpeed[0] = 30;
    animationSpeed[1] = 50;
    frameToNext = animationSpeed[0];
    speed = 4;
    position = "front";

    std::string p[] = {"front","back","left","right"} ;
    std::string t[] = {"stand","walk"} ;
    for(std::string position : p){
        for(std::string type : t){
            if(type=="stand"){
                tex_stand[position][0].loadFromFile("assets/Character/"+position+"_"+type+"_01.png");
                tex_stand[position][1].loadFromFile("assets/Character/"+position+"_"+type+"_02.png");
            }else{
                tex_walk[position][0].loadFromFile("assets/Character/"+position+"_"+type+"_01.png");
                tex_walk[position][1].loadFromFile("assets/Character/"+position+"_"+type+"_02.png");
            }

        }
    }
}

void Player::Update(){

    if(manager->inGame!=1 || (sf::Keyboard::isKeyPressed(sf::Keyboard::M) || (manager->isUsingJoystick && sf::Joystick::isButtonPressed(0,0)))){
        return;
    }

    if(frameToNext > 0) {
        frameToNext--;
    }else {
        if(isWalking()) {
            frameToNext = animationSpeed[0];
        }else {
            frameToNext = animationSpeed[1];
        }

        currFrame++;
        if(currFrame>1) {
            currFrame = 0;
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        movX = ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? 1:0 ) - ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? 1:0 ) );
        if(movX < 0) {
            position = "left";
        }else if(movX > 0) {
            position = "right";
        }
    }else{
        movX = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        movY = ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? 1:0 ) - ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? 1:0 ) );
        if(movY < 0) {
            position = "back";
        }else if(movY > 0) {
            position = "front";
        }
    }else{
        movY = 0;
    }

    if(manager->isUsingJoystick){
        movX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        movY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        if(movX<-50){
            movX = -1;
        }else if(movX>50){
            movX = 1;
        }else{
            movX = 0;
        }
        if(movY<-50){
            movY = -1;
        }else if(movY>50){
            movY = 1;
        }else{
            movY = 0;
        }
        if(movX < 0) {
            position = "left";
        }else if(movX > 0) {
            position = "right";
        }
        if(movY < 0) {
            position = "back";
        }else if(movY > 0) {
            position = "front";
        }
    }

		if(isWalking()) {
			if(!manager->CheckIfTouch(sprite.X+movX*speed, sprite.Y+80,50,50)) {
				sprite.X += movX * speed;
				if(sprite.X>=780) {
                    manager->LoadRoom(1,0);
                    SetPosition(manager->start_left);
				}
				if(sprite.X<=0) {
                    manager->LoadRoom(-1,0);
                    SetPosition(manager->start_right);
				}

			}
			if(!manager->CheckIfTouch(sprite.X, sprite.Y+movY*speed+80,50,50)) {
				sprite.Y += movY * speed;
				if(sprite.Y>=720) {
                    manager->LoadRoom(0,1);
                    SetPosition(manager->start_up);
				}
				if(sprite.Y<=-20) {
                    manager->LoadRoom(0,-1);
                    SetPosition(manager->start_down);
				}
			}
		}


    sprite.sprite.setPosition(sprite.X,sprite.Y);
    if(isWalking()){
        if(sprite.sprite.getTexture() != &tex_walk[position][currFrame]){
            sprite.sprite.setTexture(tex_walk[position][currFrame]);
        }

    }else{
        if(sprite.sprite.getTexture()!= &tex_stand[position][currFrame]){
            sprite.sprite.setTexture(tex_stand[position][currFrame]);
        }
    }

}

bool Player::isWalking(){
    return movX != 0 || movY != 0;
}

void Player::SetPosition(std::vector<int> pos){
    sprite.X = pos.at(0);
    sprite.Y = pos.at(1);
}
