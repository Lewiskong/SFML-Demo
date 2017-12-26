#include "Game.h"

Game::Game():window(sf::VideoMode(860,640),"Plane Fight")
{

}

void Game::Run()
{
    while (window.isOpen())
    {
        ProcessEvent();
        Update();
        Render();
    }
}

void Game::ProcessEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
            default:
                break;
        }
    }
}

void Game::Update()
{

}

void Game::Render()
{

}
