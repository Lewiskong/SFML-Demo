#ifndef LEIWS_GOBANG_H
#define LEWIS_GOBANG_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "ResourceHolder.h"
#include "GobangBoard.h"

class Game
{
public:
    Game();

    void Run();
    void ProcessEvent();
    void Update();
    void Render();

private:
    void InitGame();

private:
    sf::RenderWindow window;
    ResourceHolder holder;

    GobangBoard board;


};


#endif