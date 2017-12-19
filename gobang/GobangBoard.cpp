#include "GobangBoard.h"
#include <iostream>

GobangBoard::GobangBoard(size_t r,size_t c,ResourceHolder &holder):row(r),col(c),holder(holder)
{
}

void GobangBoard::Init() {
    lines.clear();

    // 初始化棋盘
    bg.setTexture(holder.GetTexture(ResourceHolder::ResourceId::REOUSRCE_CEHSSBOARD));

    // 初始化线条
    auto width = endPoint.x - startPoint.x - 2 * paddingLeft;
    auto height = endPoint.y - startPoint.y - 2 * paddingTop;
    // 横线
    std::cout<<height<<std::endl;
    float lineThick = 5.f;
    for (size_t index = 0; index <= row; index++)
    {
        auto p1 = sf::Vector2f(startPoint.x + paddingLeft, index * height / row + paddingTop - lineThick / 2);
        auto p2 = sf::Vector2f(endPoint.x - paddingLeft, index * height / row + paddingTop - lineThick / 2);

        auto p3 = sf::Vector2f(endPoint.x - paddingLeft, index * height / row + paddingTop + lineThick / 2);
        auto p4 = sf::Vector2f(startPoint.x + paddingLeft, index * height / row + paddingTop + lineThick / 2);

        lines.push_back(sf::Vertex(p1,sf::Color::Black));
        lines.push_back(sf::Vertex(p2,sf::Color::Black));
        lines.push_back(sf::Vertex(p3,sf::Color::Black));
        lines.push_back(sf::Vertex(p4,sf::Color::Black));
    }
    // 竖线
    for (size_t index = 0; index <= col; index++)
    {
        auto p1 = sf::Vector2f(index * width / col + paddingLeft - lineThick/2, startPoint.y + paddingTop);
        auto p2 = sf::Vector2f(index * width / col + paddingLeft - lineThick/2, endPoint.y - paddingTop);

        auto p3 = sf::Vector2f(index * width / col + paddingLeft + lineThick / 2, endPoint.y - paddingTop);
        auto p4 = sf::Vector2f(index * width / col + paddingLeft + lineThick / 2, startPoint.y + paddingTop);

        lines.push_back(sf::Vertex(p1,sf::Color::Black));
        lines.push_back(sf::Vertex(p2,sf::Color::Black));
        lines.push_back(sf::Vertex(p3,sf::Color::Black));
        lines.push_back(sf::Vertex(p4,sf::Color::Black));
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


void GobangBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.clear();
    target.draw(bg,states);

    // 画棋盘的线条
    target.draw(&lines[0],lines.size(),sf::Quads);

    // 画棋子

}
