#include "MiniMap.h"
#include <SFML/Graphics.hpp>
#include <vector>

MiniMap::MiniMap()
{
    //BG = 0
    //Haut-gauche = 1
    //Haut = 2
    //Haut-droite = 3
    //Centre-gauche = 4
    //Centre = 5
    //Centre-droite = 6
    //Bas-gauche = 7
    //Bas = 8
    //Bas-droite = 9


    shapes[0].setSize(sf::Vector2f(100,100));
    shapes[0].setFillColor(sf::Color(0,0,0));

    for(int i = 1;i<10;i++){
        shapes[i].setSize(sf::Vector2f(30,30));
    }

    shapes[2].setPosition(35,0);
    shapes[3].setPosition(70,0);
    shapes[4].setPosition(0,35);
    shapes[5].setPosition(35,35);
    shapes[6].setPosition(70,35);
    shapes[7].setPosition(0,70);
    shapes[8].setPosition(35,70);
    shapes[9].setPosition(70,70);

    shapes[5].setFillColor(sf::Color(200,200,200));

}
