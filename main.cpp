#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "shapes.h"
#include "Gobang.h"

#define Ot std::cout<<"hello"<<std::endl;

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600),"My Window");

    Gobang gobang(window,16,0.9f);
    gobang.InitBoard();

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {

                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    gobang.InitBoard();
                    break;
                default:
                    break;
            }
        }


//        Asterisk ast(250);
//
//        ast.setPosition(350,350);
//
//        sf::Texture texture;
//        if (!texture.loadFromFile("/Users/nirvana/Documents/素材/壁纸/2017-10-29_1.jpg"))
//        {
//            std::cerr<<"load file error"<<std::endl;
//            return -1;
//        }
//        ast.setTexture(&texture);
//
//        window.draw(ast);



    }

}
