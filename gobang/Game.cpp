#include "Game.h"

#include <iostream>
#include <string>
#include <sstream>

Game::Game():window(sf::VideoMode(860,860),"Gobang Game"),board(16,16,holder)
{
    holder.LoadTexture(ResourceHolder::ResourceId::RESOURCE_CHESSBOARD,"../gobang/resources/board.jpeg");
    holder.LoadTexture(ResourceHolder::ResourceId::RESOURCE_BLACK_CHESS,"../gobang/resources/black.png");
    holder.LoadTexture(ResourceHolder::ResourceId::RESOURCE_WHITE_CHESS,"../gobang/resources/white.png");

    board.setRect(sf::Vector2f(0.f,0.f),sf::Vector2f(window.getSize().x,window.getSize().y));
    board.setPadding(30.f);
    board.Init();

    InitGame();

    // 初始化网络模块
    auto netThread = isServer ? std::unique_ptr<std::thread>(new std::thread(&Game::dataInteractServer, this)):
                                std::unique_ptr<std::thread>(new std::thread(&Game::dataInteractClient, this));
    net=std::move(netThread);
    net->detach();

    isMyTurn=isServer;
}

void Game::dataInteractServer()
{
    sf::TcpListener listener;

    auto port = 34567;

    if (listener.listen(port)!=sf::Socket::Done)
    {
        std::cerr<<"port "<<port<<" has been used!"<<std::endl;
        exit(1);
    }

    if (listener.accept(socket)!=sf::Socket::Done)
    {
        std::cerr<<"Tcp accept failed."<<std::endl;
        exit(1);
    }
    std::cout<<"connect success"<<std::endl;
    while (true)
    {
        sf::Packet packet;
        if (socket.receive(packet)!=sf::Socket::Done) break;
        std::string msg;
        packet>>msg;
        std::cout<<msg<<std::endl;

        Message m;
        m.parse(msg);

        handleMessage(m);
    }

}

void Game::dataInteractClient() {
    auto port = 34567;
    if (socket.connect("localhost", port) != sf::Socket::Done)
    {
        std::cerr<<"Tcp connect failed."<<std::endl;
        exit(1);
    }
    std::cout<<"connect success"<<std::endl;
    while (true)
    {
        sf::Packet packet;
        if (socket.receive(packet)!=sf::Socket::Done) break;
        std::string msg;
        packet>>msg;
        std::cout<<msg<<std::endl;

        Message m;
        m.parse(msg);

        handleMessage(m);
    }
}

void Game::handleMessage(const Message &m)
{
    hasChessPower.lock();

    // 处理消息
    switch (m.cmd)
    {
        case Message::CMD_PUT_CHESS:
            if (!isMyTurn)
            {
                // 下子
                gobang::ChessType  tp = isServer?gobang::WhiteChess:gobang::BlackChess;
                board.Put(sf::Vector2i(m.x,m.y),tp);
                isMyTurn=!isMyTurn;
            }
            break;
        case Message::CMD_GIVE_UP:
            break;
        case Message::CMD_REGRET:
            break;
        default:
            break;
    }

    hasChessPower.unlock();
}

void Game::Run()
{
    board.myChesspiece = isServer?gobang::BlackChess:gobang::WhiteChess;
    window.setFramerateLimit(30);
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
                if (event.mouseButton.button==sf::Mouse::Button::Left) PutChessPiece(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                break;
            default:
                break;
        }
    }
}

void Game::Update() {

}

void Game::Render() {
    window.clear();
    window.draw(board);

    window.display();
}


void Game::InitGame() {
    window.clear();
    window.draw(board);

    window.display();
}


void Game::PutChessPiece(sf::Vector2i pos) {

    if (!isMyTurn) return;

    hasChessPower.lock();
    auto ret = board.Put(pos,board.myChesspiece);


    switch (ret)
    {
        case gobang::PutFail:
            break;
        case gobang::Win:
            exit(1);
        case gobang::PutSucceed:
            // 同步消息
            sf::Packet packet;
            Message m;
            m.cmd = Message::CMD_PUT_CHESS;
            m.x = pos.x;
            m.y = pos.y;
            packet<<m.toString();
            socket.send(packet);

            // 更换走子玩家
            isMyTurn=!isMyTurn;
            break;
    }

    hasChessPower.unlock();

}


