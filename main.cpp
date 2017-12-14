#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "shapes.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600),"My Window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type==sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        sf::CircleShape circle(50);
        circle.setFillColor(sf::Color(150,50,250));
        circle.setOutlineThickness(10);
        circle.setOutlineColor(sf::Color(250,150,100));
        circle.setPosition(30,30);

        sf::CircleShape triangle(50,5);
        triangle.setFillColor(sf::Color(20,100,88));
        triangle.setPosition(30,30);

        Asterisk ast(250);

        ast.setPosition(350,350);

        sf::Texture texture;
        if (!texture.loadFromFile("/Users/nirvana/Documents/素材/壁纸/2017-10-29_1.jpg"))
        {
            std::cerr<<"load file error"<<std::endl;
            return -1;
        }
        ast.setTexture(&texture);


//        window.draw(circle);
//        window.draw(triangle);
        window.draw(ast);



        window.display();

    }

}
