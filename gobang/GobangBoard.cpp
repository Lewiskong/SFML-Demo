#include "GobangBoard.h"
#include <iostream>

GobangBoard::GobangBoard(size_t r,size_t c,ResourceHolder &holder):row(r),col(c),holder(holder)
{
}

void GobangBoard::Init() {
    lines.clear();
    points.clear();

    // 初始化棋盘
    bg.setTexture(holder.GetTexture(ResourceHolder::ResourceId::RESOURCE_CHESSBOARD));

    // 初始化线条
    auto width = endPoint.x - startPoint.x - 2 * paddingLeft;
    auto height = endPoint.y - startPoint.y - 2 * paddingTop;
    // 横线
    float lineThick = 5.f;
    for (size_t index = 0; index <= row; index++)
    {
        auto p1 = sf::Vector2f(startPoint.x + paddingLeft, startPoint.y + index * height / row + paddingTop - lineThick / 2);
        auto p2 = sf::Vector2f(endPoint.x - paddingLeft, startPoint.y + index * height / row + paddingTop - lineThick / 2);

        auto p3 = sf::Vector2f(endPoint.x - paddingLeft, startPoint.y + index * height / row + paddingTop + lineThick / 2);
        auto p4 = sf::Vector2f(startPoint.x + paddingLeft, startPoint.y + index * height / row + paddingTop + lineThick / 2);

        lines.push_back(sf::Vertex(p1,sf::Color::Black));
        lines.push_back(sf::Vertex(p2,sf::Color::Black));
        lines.push_back(sf::Vertex(p3,sf::Color::Black));
        lines.push_back(sf::Vertex(p4,sf::Color::Black));
    }
    // 竖线
    for (size_t index = 0; index <= col; index++)
    {
        auto p1 = sf::Vector2f(startPoint.x + index * width / col + paddingLeft - lineThick/2, startPoint.y + paddingTop);
        auto p2 = sf::Vector2f(startPoint.x + index * width / col + paddingLeft - lineThick/2, endPoint.y - paddingTop);

        auto p3 = sf::Vector2f(startPoint.x + index * width / col + paddingLeft + lineThick / 2, endPoint.y - paddingTop);
        auto p4 = sf::Vector2f(startPoint.x + index * width / col + paddingLeft + lineThick / 2, startPoint.y + paddingTop);

        lines.push_back(sf::Vertex(p1,sf::Color::Black));
        lines.push_back(sf::Vertex(p2,sf::Color::Black));
        lines.push_back(sf::Vertex(p3,sf::Color::Black));
        lines.push_back(sf::Vertex(p4,sf::Color::Black));
    }

    // 初始化棋子结构
    for (size_t i=0;i<=row;i++)
    {
        for (size_t j=0;j<=col;j++)
        {
            std::unique_ptr<GobangChessPiece> pt(new GobangChessPiece(sf::Vector2f(startPoint.x + j * width / col + paddingLeft,
                                                                         startPoint.y + i * height / row + paddingTop),*this));
            points.push_back(std::move(pt));
        }
    }

}

void GobangBoard::setRect(sf::Vector2f start, sf::Vector2f end) {
    startPoint = start;
    endPoint = end;

    Init();
}

void GobangBoard::setPadding(float paddingTop, float paddingLeft) {
    if (paddingLeft == 0.f) paddingLeft = paddingTop;
    this->paddingTop = paddingTop;
    this->paddingLeft = paddingLeft;

    Init();
}

GobangBoard::PutState GobangBoard::Put(sf::Vector2i pos,GobangChessPiece::ChessType tp)
{
    // 下子精度
    float precision = 15.f;
    for ( auto &item : points)
    {
        if (pos.x >= item->pos.x - precision && pos.x <= item->pos.x + precision &&
            pos.y >= item->pos.y - precision && pos.y <= item->pos.y + precision)
        {
            if (tp != GobangChessPiece::NoChess && item->getType() == GobangChessPiece::BlackChess ||
                item->getType() == GobangChessPiece::WhiteChess)
                return PutState::PutFail;
            item->setType(tp);
            if (CheckWin(item->index)) return GobangBoard::PutState::Win;
            return GobangBoard::PutState::PutSucceed;
        }
    }
    return GobangBoard::PutState::PutFail;
}

bool GobangBoard::CheckWin(int index) {
    return true;
}


void GobangBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.clear();
    target.draw(bg,states);

    // 画棋盘的线条
    target.draw(&lines[0],lines.size(),sf::Quads);

    // 画棋子
    for (auto &it : points)
    {
        target.draw(*it);
    }


}














/// class ChessPoint

GobangChessPiece::GobangChessPiece(sf::Vector2f pos, GobangBoard &board, int index,
                                   GobangChessPiece::ChessType type) : pos(pos), board(board),index(index), type(type)
{

}

void GobangChessPiece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (type==BlackChess || type==WhiteChess)
    {
        target.draw(chesspiece,states);
    }
}

void GobangChessPiece::setType(ChessType tp) {
    if (tp==NoChess)
    {
        chesspiece.setScale(0.f,0.f);
        return;
    }

    if (tp==BlackChess) chesspiece.setTexture(board.holder.GetTexture(ResourceHolder::ResourceId::RESOURCE_BLACK_CHESS));
    else chesspiece.setTexture(board.holder.GetTexture(ResourceHolder::ResourceId::RESOURCE_WHITE_CHESS));

    auto width = board.endPoint.x - board.startPoint.x - 2 * board.paddingLeft;
    auto height = board.endPoint.y - board.startPoint.y - 2 * board.paddingTop;
    auto chesspieceWidth = chesspiece.getGlobalBounds().width;
    auto chesspieceHeight = chesspiece.getGlobalBounds().height;

    chesspiece.setPosition(this->pos);
    chesspiece.setOrigin(chesspieceWidth/2,chesspieceHeight/2);

    chesspiece.setScale(width/board.col/chesspieceWidth,height/board.row/chesspieceHeight);
    type=tp;

}
