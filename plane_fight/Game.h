#ifndef LEWIS_PLANE_FIGHT_GAME_H
#define LEWIS_PLANE_FIGHT_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game();
    void Run();

    void ProcessEvent();
    void Update();
    void Render();

private:
    sf::RenderWindow window;
};

#endif