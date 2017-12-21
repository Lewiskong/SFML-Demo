#include "GobangBoard.h"
#include <iostream>

GobangBoard::GobangBoard(size_t r,size_t c,ResourceHolder &holder):row(r),col(c),holder(holder)
{
}

void GobangBoard::Init() {
    lines.clear();
    points.clear();

    /// 初始化棋盘
    bg.setTexture(holder.GetTexture(ResourceHolder::ResourceId::RESOURCE_CHESSBOARD));

    /// 初始化线条
    auto width = endPoint.x - startPoint.x - 2 * paddingLeft;
    auto height = endPoint.y - startPoint.y - 2 * paddingTop;
    // 横线
    float lineThick = 4.f;
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

    /// 初始化棋子结构
    int index=0;
    for (size_t i=0;i<=row;i++)
    {
        for (size_t j=0;j<=col;j++)
        {
            std::unique_ptr<GobangChessPiece> pt(new GobangChessPiece(sf::Vector2f(startPoint.x + j * width / col + paddingLeft,
                                                                         startPoint.y + i * height / row + paddingTop),*this));
            pt->index=index++;
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

gobang::PutState GobangBoard::Put(sf::Vector2i pos)
{
    // 下子精度
    float precision = 15.f;
    for ( auto &item : points)
    {
        if (pos.x >= item->pos.x - precision && pos.x <= item->pos.x + precision &&
            pos.y >= item->pos.y - precision && pos.y <= item->pos.y + precision)
        {
            if ( (myChesspiece != gobang::NoChess && item->getType() == gobang::BlackChess) ||
                item->getType() == gobang::WhiteChess)
                return gobang::PutFail;
            item->setType(myChesspiece);
            if (CheckWin(item->index)) return gobang::Win;
            return gobang::PutSucceed;
        }
    }
    return gobang::PutFail;
}

///       xxx
///       xox
///       xxx
bool GobangBoard::CheckWin(int index) {
    auto color = points[index]->getType();

    auto isLineWin = [color, index , this](int delta,size_t min,size_t max) -> bool {
        int cnt = 1;
        int tmp1 = index - delta, tmp2 = index + delta;
        while (tmp1 >= int(min)) {
            if (points[tmp1]->getType() == color) cnt++;
            else break;
            tmp1 -= delta;
        }
        while (tmp2 < int(max)) {
            if (points[tmp2]->getType() == color) cnt++;
            else break;
            tmp2 += delta;
        }
        return cnt>=5;
    };

    // 判断上下方向
    if (isLineWin(int(col + 1), 0, points.size())) return true;

    // 判断左右方向
    if (isLineWin(1, index / (col + 1) * (col + 1), (1 + index / (col + 1)) * (col + 1))) return true;

    // 判断 / 方向
    if (isLineWin(int(col), 0, points.size())) return true;

    // 判断 \ 方向
    return isLineWin(int(col - 1), 0, points.size());

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
                                   gobang::ChessType type) : pos(pos), board(board),index(index), type(type)
{

}

void GobangChessPiece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (type==gobang::BlackChess || type==gobang::WhiteChess)
    {
        target.draw(chesspiece,states);
    }
}

void GobangChessPiece::setType(gobang::ChessType tp) {
    if (tp==gobang::NoChess)
    {
        chesspiece.setScale(0.f,0.f);
        return;
    }

    if (tp==gobang::BlackChess) chesspiece.setTexture(board.holder.GetTexture(ResourceHolder::ResourceId::RESOURCE_BLACK_CHESS));
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
