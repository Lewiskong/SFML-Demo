#include "Game.h"

Game::Game():window(sf::VideoMode(860,860),"Gobang Game"),board(16,16,holder)
{
    holder.LoadTexture(ResourceHolder::ResourceId::REOUSRCE_CEHSSBOARD,"../gobang/resources/board.jpeg");

    board.setRect(sf::Vector2f(0.f,0.f),sf::Vector2f(window.getSize().x,window.getSize().y));
    board.setPadding(30.f);
    board.Init();

    InitGame();
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

void Game::ProcessEvent() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                break;
            default:
                break;
        }
    }
}

void Game::Update() {

}

void Game::Render() {

}


void Game::InitGame() {
    window.clear();
    window.draw(board);

    window.display();
}

