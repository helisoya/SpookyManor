#include <iostream>
#include <SFML/Graphics.hpp>
#include <ManorManager.h>
#include <Player.h>
#include <MiniMap.h>
#include <MonsterOne.h>
#include <SpriteComponent.h>
#include <MonsterTwo.h>
#include <MonsterThree.h>
#include <MonsterFour.h>
#include <MonsterFive.h>
#include <MonsterSix.h>
#include <Monster.h>

using namespace std;

ManorManager manager;

Player player;
std::vector<Monster*> monsters;

MiniMap minimap;

std::vector<SpriteComponent*> sprites;

bool compareDepth(SpriteComponent* a, SpriteComponent* b) { return (a->Y+a->sprite.getTexture()->getSize().y < b->Y+b->sprite.getTexture()->getSize().y); }

sf::RenderWindow window(sf::VideoMode(800, 800), "Spooky Manor",sf::Style::Titlebar | sf::Style::Close);

void DrawWalls(){
    for(int i = 0;i<manager.walls.size();i++){
        if(manager.walls.at(i)->drawable){
            window.draw(manager.walls.at(i)->shape);
        }
    }
}

void DrawMinimap(){
    for(int i = 0;i<10;i++){
        window.draw(minimap.shapes[i]);
    }
}

void DrawSprites(){
    for(int i =0;i<sprites.size();i++){
        if(sprites.at(i)->drawable){
            window.draw(sprites.at(i)->sprite);
        }
    }
}


int main()
{

    MonsterOne* m_01 = new MonsterOne();
    MonsterTwo* m_02 = new MonsterTwo();
    MonsterThree* m_03 = new MonsterThree();
    MonsterFour* m_04 = new MonsterFour();
    MonsterFive* m_05 = new MonsterFive();
    MonsterSix* m_06 = new MonsterSix();
    monsters.push_back(m_01);
    monsters.push_back(m_02);
    monsters.push_back(m_03);
    monsters.push_back(m_04);
    monsters.push_back(m_05);
    monsters.push_back(m_06);

    manager.monsters = &monsters;

    sprites.push_back(&player.sprite);

    for(int i = 0;i < monsters.size();i++){
        sprites.push_back(&monsters.at(i)->sprite);
        monsters.at(i)->manager = &manager;
    }


    manager.player = &player;
    manager.minimap = &minimap;

    player.manager = &manager;


    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    window.setIcon(32,32,icon.getPixelsPtr());
    window.setFramerateLimit(60);

    sf::Texture filter_t;
    filter_t.loadFromFile("assets/screen.png");
    sf::Sprite filter_s;
    filter_s.setTexture(filter_t);

    sf::Texture logo_t;
    logo_t.loadFromFile("assets/logo.png");
    sf::Sprite logo_s;
    logo_s.setTexture(logo_t);
    logo_s.setPosition(180,300);

    sf::Texture win_t;
    win_t.loadFromFile("assets/win.png");
    sf::Sprite win_s;
    win_s.setTexture(win_t);
    win_s.setPosition(250,300);
    int end = 800;
    sf::RectangleShape win_r;
    win_r.setSize(sf::Vector2f(800,800));
    win_r.setFillColor(sf::Color(0,0,0));

    sf::Font font;
    font.loadFromFile("assets/font.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setPosition(300,450);
    text.setString("Click to Play");

    sf::Texture statics[22];
    sf::Sprite static_s;
    int currStatic = 0;
    int FrameToNextStatic = 2;
    for(int i = 1;i<22;i++){
        statics[i-1].loadFromFile("assets/Static/"+std::to_string(i)+".png");
    }
    static_s.setTexture(statics[0]);

    bool MapUpdated = false;


    while (window.isOpen())
    {

        if(sf::Joystick::isConnected(0)){
            if(manager.isUsingJoystick!=true){
                manager.isUsingJoystick=true;
            }
        }else if(manager.isUsingJoystick!=false){
            manager.isUsingJoystick=false;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();



        }

        if(manager.inGame==0){
            window.clear();
            window.draw(logo_s);
            window.draw(text);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || (manager.isUsingJoystick && sf::Joystick::isButtonPressed(0,0))){

                manager.inGame = 1;
                player.SetPosition(manager.start_middle);
                manager.Reset();
            }

        }else if(manager.inGame==1){


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M) || (manager.isUsingJoystick && sf::Joystick::isButtonPressed(0,0))){
            if(!MapUpdated){
                MapUpdated = true;
            }
            window.clear(manager.minimap_bg);
            for(int i = 0;i<manager.maze.maze.size();i++){
                for(int j = 0;j<manager.maze.maze.size();j++){
                    window.draw(manager.maze.maze.at(j).at(i).map_shape);
                }
            }
        }else{
            if(MapUpdated){
                MapUpdated = false;
            }
            player.Update();
            for(int i = 0;i < monsters.size();i++){
                monsters.at(i)->Update();
            }
            window.clear(manager.color_floor);

            DrawWalls();

            std::sort(sprites.begin(), sprites.end(),compareDepth);

            DrawSprites();
            DrawMinimap();
        }
        window.draw(filter_s);

        }else if(manager.inGame==2){
            window.clear();
            window.draw(static_s);
			if(FrameToNextStatic>0) {
				FrameToNextStatic--;
			}else{
				FrameToNextStatic = 2;
				if(currStatic == 22) {
					currStatic = 0;
					manager.inGame = 0;
					manager.sound.stop();
					static_s.setTexture(statics[0]);
				}else {
					currStatic++;
					static_s.setTexture(statics[currStatic]);
				}
			}

        }else{
			if(end != 0) {
                win_r.setSize(sf::Vector2f(800,end));
				window.clear(sf::Color(255,255,255));
				window.draw(win_s);
				window.draw(win_r);
				end-=2;
			}else {
				end = 800;
				manager.inGame = 0;
			}
        }

        window.display();


    }

    return 0;
}

