#ifndef LEWIS_GOBANG_BOARD_H
#define LEWIS_GOBANG_BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"


class GobangBoard : public sf::Drawable,public sf::Transformable
{
public:
    GobangBoard(size_t r,size_t c,ResourceHolder &holder);
    void Init();
    void setRect(sf::Vector2f start,sf::Vector2f end);
    void setPadding(float paddingTop,float paddingLeft=0.f);
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Sprite bg;
    ResourceHolder &holder;

    size_t row,col;
    sf::Vector2f startPoint,endPoint;
    std::vector<sf::Vertex> lines;
    float paddingTop,paddingLeft;

};


#endif
