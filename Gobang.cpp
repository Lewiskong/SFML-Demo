#include "Gobang.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

void Gobang::InitBoard()
{
    auto &window=this->window;
    window.clear(sf::Color::Black);

    auto width=uint(window.getSize().x * this->percent);
    auto height=uint(window.getSize().y * this->percent);

    std::vector<sf::Vertex> lines;
    for (size_t index=0;index<=size;index++)
    {
        auto hPadding = width*(1-percent)/2;
        auto vPadding = height*(1-percent)/2;

        auto HStartPoint = sf::Vector2f(0 + hPadding, 1.0f * index / size * height * percent + vPadding);
        auto HEndPoint = sf::Vector2f(1 * width * percent + hPadding,
                                      1.0f * index / size * height * percent + vPadding);
        auto VStartPoint = sf::Vector2f(1.0f * index / size * width * percent + hPadding, 0 + vPadding);
        auto VEndPoint = sf::Vector2f(1.0f * index / size * width * percent + hPadding,
                                      1 * height * percent + vPadding);

        lines.push_back(sf::Vertex(HStartPoint));
        lines.push_back(sf::Vertex(HEndPoint));
        lines.push_back(sf::Vertex(VStartPoint));
        lines.push_back(sf::Vertex(VEndPoint));

    }

    window.draw(&lines[0],lines.size(),sf::Lines);
    window.display();

}

