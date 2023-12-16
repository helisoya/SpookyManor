#include "MonsterFive.h"
#include <ManorManager.h>
#include <SpriteComponent.h>
#include <Player.h>

MonsterFive::MonsterFive()
{
    SpawnAfterFrame = -1;
    sprite.drawable = false;
    movX = 0;
    movY = 0;
    position = "front";
    speed = 1;
    std::string p[] = {"front","back","left","right"} ;
    for(std::string position : p){
        texs[position].loadFromFile("assets/Monster05/"+position+".png");
    }
    sprite.sprite.setTexture(texs[position]);
}

void MonsterFive::Update(){
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

    sprite.sprite.setPosition(sprite.X,sprite.Y);
    if(sprite.sprite.getTexture() != &texs[position]){
        sprite.sprite.setTexture(texs[position]);
    }

    if(sprite.X - 30 < manager->player->sprite.X + 25 && manager->player->sprite.X + 25 < sprite.X + 90
       && sprite.Y +100 < manager->player->sprite.Y + 125 && manager->player->sprite.Y + 125 < sprite.Y + 200) {
        manager->inGame = 2;
        manager->PlaySound(&(manager->sfx_static));
    }

    if(sprite.Y<manager->player->sprite.Y && manager->player->position == "back" ||
       sprite.Y>manager->player->sprite.Y && manager->player->position == "front" ||
       sprite.X<manager->player->sprite.X && manager->player->position == "left" ||
       sprite.X>manager->player->sprite.X && manager->player->position == "right"){
            return;
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
        sprite.X+=speed*movX;
        sprite.Y+=speed*movY;


}


void MonsterFive::SetPosition(std::vector<int> pos){
    sprite.X = pos.at(0);
    sprite.Y = pos.at(1);
}
