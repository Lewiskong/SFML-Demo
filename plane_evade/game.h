#ifndef LEWIS_GAME_H
#define LEWIS_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "components.h"


class Game
{
public:
    Game();
    void Run();
    void Restart();

private:
    void ProcessEvents();
    void Update(sf::Time interval);
    void Render();

    void GenerateBullets();

    sf::RenderWindow window;
    Plane player;
    std::vector<Bullet> bullets;
    sf::Text times;
    sf::Font font;
    sf::Sound bgMusic;
    sf::SoundBuffer bgMusicBuffer;


    float speed;
    float rotateSpeed;
    size_t fps;
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