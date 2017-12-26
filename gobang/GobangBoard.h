#ifndef LEWIS_GOBANG_BOARD_H
#define LEWIS_GOBANG_BOARD_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

class GobangBoard;

namespace gobang{
    enum ChessType{
        NoChess,
        BlackChess,
        WhiteChess
    };
    enum PutState {
        Win,
        PutFail,
        PutSucceed
    };
}

class GobangChessPiece : public sf::Drawable,public sf::Transformable
{
public:

    GobangChessPiece(sf::Vector2f pos, GobangBoard &board, int index = 0,
                     gobang::ChessType type = gobang::ChessType::NoChess);
    GobangChessPiece() = default;

    void setType(gobang::ChessType tp);
    gobang::ChessType getType() {return type;}

    sf::Vector2f pos;
    int index;
private:
    sf::Sprite chesspiece;
    gobang::ChessType type;
    GobangBoard &board;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class GobangBoard : public sf::Drawable,public sf::Transformable
{
    friend class GobangChessPiece;
public:
    GobangBoard(size_t r,size_t c,ResourceHolder &holder);
    void Init();
    void setRect(sf::Vector2f start,sf::Vector2f end);
    void setPadding(float paddingTop,float paddingLeft=0.f);

    gobang::PutState Put(sf::Vector2i pos,gobang::ChessType type);

    gobang::ChessType myChesspiece;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool CheckWin(int index);

private:
    std::vector<std::unique_ptr<GobangChessPiece>> points;

    sf::Sprite bg;
    ResourceHolder &holder;

    size_t row,col;
    sf::Vector2f startPoint,endPoint;
    std::vector<sf::Vertex> lines;
    float paddingTop,paddingLeft;

};


#endif
