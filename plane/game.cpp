#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Game::Game():window(sf::VideoMode(860,640),"Plane Game"),player(window),speed(300.f),fps(60),rotateSpeed(180.f)
{
    player.setOrigin(player.getTextureRect().width/2,player.getTextureRect().height/2);
    player.setScale(2.f,2.f);
    player.setPosition(window.getSize().x/2.f,window.getPosition().y/2.f);
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate=sf::Time::Zero;

    std::cout<<bullets.size()<<std::endl;

    while (window.isOpen())
    {
        auto time=clock.restart();
        timeSinceLastUpdate+=time;
        while (timeSinceLastUpdate.asSeconds()>1.f/fps)
        {
            auto timePerFrame = sf::seconds(1.f / fps);
            timeSinceLastUpdate -= timePerFrame;

            ProcessEvents();
            Update(timePerFrame);
        }
        Render();
        if (isOver) break;

    }
}

void Game::ProcessEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                HandlePlayerInput(event.key.code,true);
                break;
            case sf::Event::KeyReleased:
                HandlePlayerInput(event.key.code,false);
                break;
            default:
                break;
        }
    }
}

void Game::Update(sf::Time interval)
{
    //产生子弹
    if (rand()%20 >= 18) GenerateBullets();



    //update bullets
    for (auto it = bullets.begin();it!=bullets.end();)
    {
        it->Move(interval);

        //检测是否与飞机碰撞
        if (it->isCollide(player)) isOver=true;

        if (it->isOut()) it = bullets.erase(it);
        else it++;
    }

    sf::Vector2f pos(0.f,0.f);

    auto pace = speed * interval.asSeconds();

    if (direction.isUp) pos.y-=pace;
    if (direction.isDown) pos.y+=pace;
    if (direction.isLeft) pos.x-=pace;
    if (direction.isRight) pos.x+=pace;
    if (direction.isRotateLeft) player.rotate(-rotateSpeed*1.f/fps);
    if (direction.isRotateRight) player.rotate(rotateSpeed*1.f/fps);

    player.Move(pos);
}

void Game::Render()
{
    window.clear();

    window.draw(player);

    //draw bullets
    for (auto &item:bullets)
    {
        window.draw(item);
    }

    window.display();
}

void Game::HandlePlayerInput(sf::Keyboard::Key k, bool isPressed)
{
    switch (k)
    {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            direction.isUp=isPressed;
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            direction.isDown=isPressed;
            break;
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            direction.isLeft=isPressed;
            break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            direction.isRight=isPressed;
            break;
        case sf::Keyboard::Q:
            direction.isRotateLeft=isPressed;
            break;
        case sf::Keyboard::E:
            direction.isRotateRight=isPressed;
            break;
        default:
            break;
    }
}


void Game::GenerateBullets()
{
//    float size = rand()%3 + 1.f;
    float size = 2.f;

    // 为了整洁，暂时忽略效率影响
    auto rd = [](uint val)->float{
        return rand()%val;
    };
    auto GetRandomPosition = [this,rd]()->sf::Vector2f{
        auto screen = this->window.getSize();
        auto flag = rand()%4;
        switch (flag)
        {
            case 0:
                return sf::Vector2f(rd(screen.x),0);
            case 1:
                return sf::Vector2f(screen.x,rd(screen.y));
            case 2:
                return sf::Vector2f(rd(screen.x),screen.y);
            case 3:
                return sf::Vector2f(0,rd(screen.y));
            default:
                break;
        }
        return sf::Vector2f(0,0);
    };

    Bullet bullet(GetRandomPosition(),player,&window,size);

    bullets.push_back(bullet);
}
