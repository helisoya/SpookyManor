#include "Monster.h"

Monster::Monster()
{
    SpawnAfterFrame = -1;
    sprite.drawable = false;
    movX = 0;
    movY = 0;
    speed = 1;
}

void Monster::Update(){
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

    MonsterLogic();
}


void Monster::SetPosition(std::vector<int> pos){
    sprite.X = pos.at(0);
    sprite.Y = pos.at(1);
}

void Monster::MonsterLogic(){
}
