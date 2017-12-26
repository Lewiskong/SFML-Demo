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
#include <string>
#include <sstream>

struct Message;

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
    void handleMessage(const Message& m);
private:
    sf::RenderWindow window;
    ResourceHolder holder;

    GobangBoard board;

    std::unique_ptr<std::thread> net;


    std::mutex hasChessPower; ///是否拥有棋权
    sf::TcpSocket socket;


    bool isServer = false; /// 标志棋盘服务器端或者客户端
    bool isMyTurn;
};

struct Message
{
    enum CMD {
        CMD_PUT_CHESS=0,
        CMD_GIVE_UP,
        CMD_REGRET
    };
    CMD cmd;
    int x;
    int y;

    std::string toString()
    {
        std::stringstream ss;
        ss<<cmd;
        ss<<".";
        ss<<x;
        ss<<".";
        ss<<y;
        ss<<".";
        return ss.str();
    }

    void parse(std::string str)
    {
        auto tmp=str;
        size_t index=0;
        int cnt=0;
        while ( (index=tmp.find("."))!=std::string::npos)
        {
            auto v = tmp.substr(0,index);
            tmp=tmp.substr(index+1);
            if (cnt == 0) cmd = (CMD) std::stoi(v);
            else if (cnt==1) x = std::stoi(v);
            else if (cnt==2) y = std::stoi(v);
            cnt++;
        }
    }

};


#endif