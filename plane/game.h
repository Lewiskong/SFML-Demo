#ifndef LEWIS_GAME_H
#define LEWIS_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "components.h"


class Game
{
public:
    Game();
    void Run();

private:
    void ProcessEvents();
    void Update(sf::Time interval);
    void Render();

    void GenerateBullets();

    sf::RenderWindow window;


    float speed;
    float rotateSpeed;
    size_t fps;

    std::vector<Bullet> bullets;
    Plane player;
    bool isOver;

    void HandlePlayerInput(sf::Keyboard::Key k,bool isPressed);
    struct  {
        bool isUp = false;
        bool isDown = false;
        bool isLeft = false;
        bool isRight = false;
        bool isRotateLeft = false;
        bool isRotateRight = false;
    } direction;
};


#endif