#ifndef LEWIS_GOBANG_H
#define LEWIS_GOBANG_H

#include "ResourceHolder.h"
#include "GobangBoard.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <thread>
#include <mutex>
#include <iostream>
#include <memory>

class Game
{
public:
    Game();

    void Run();
    void ProcessEvent();
    void Update();
    void Render();

    void PutChessPiece(sf::Vector2i pos);

private:
    void InitGame();

    // 网络模块数据交互
    void dataInteractServer();
    void dataInteractClient();
    // 处理接受到的消息
    void handleMessage();
private:
    sf::RenderWindow window;
    ResourceHolder holder;

    GobangBoard board;

    std::unique_ptr<std::thread> net;


    std::mutex hasChessPower; ///是否拥有棋权
    sf::TcpSocket socket;


    bool isServer = false; /// 标志棋盘服务器端或者客户端

};


#endif