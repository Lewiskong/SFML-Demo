#include "components.h"
#include <math.h>
#include <iostream>


/**
*   Class Bullet
*
*
*
*
*
*
*/
Bullet::Bullet(const sf::Vector2f &pos, sf::Transformable &target,sf::RenderTarget *renderTarget, float r, float sp) : sf::CircleShape(r), speed(sp),window(renderTarget)
{
    auto targetPos = target.getPosition();

    //set direction
    direction=targetPos - pos;
    direction/=sqrtf(direction.x*direction.x+direction.y*direction.y);

    // set position
    setPosition(pos);

    // set radius
    setRadius(r);
}

void Bullet::Move(const sf::Time &time)
{
//    std::cout<<getPosition().x<<" "<<getPosition().y<<std::endl;
    move(direction*time.asSeconds()*speed);
}

bool Bullet::isOut()
{
    auto width = window->getSize().x;
    auto height = window->getSize().y;

    return getPosition().x < 0 || getPosition().x > width || getPosition().y < 0 || getPosition().y > height;
}

bool Bullet::isCollide(const Plane &plane)
{
//    auto bd = plane.getGlobalBounds();

    auto p1 = sf::Vector2f(getGlobalBounds().left,getGlobalBounds().top);
    auto p2 = sf::Vector2f(getGlobalBounds().left+getGlobalBounds().width,getGlobalBounds().top);
    auto p3 = sf::Vector2f(getGlobalBounds().left,getGlobalBounds().top+getGlobalBounds().height);
    auto p4 = sf::Vector2f(getGlobalBounds().left+getGlobalBounds().width,getGlobalBounds().top+getGlobalBounds().height);

    auto planePoint1 = sf::Vector2f(plane.getGlobalBounds().left,plane.getGlobalBounds().top);
    auto planePoint2 = sf::Vector2f(plane.getGlobalBounds().left+plane.getGlobalBounds().width,plane.getGlobalBounds().top+plane.getGlobalBounds().height);

    auto inRect = [planePoint1,planePoint2](const sf::Vector2f &pt){
        return pt.x > planePoint1.x && pt.x < planePoint2.x && pt.y > planePoint1.y && pt.y < planePoint2.y;
    };

    return inRect(p1) || inRect(p2) || inRect(p3) || inRect(p4);
}



/**
*   Class Plane
*
*
*
*
*
*
*/
Plane::Plane(sf::RenderTarget &window):target(window)
{
    if (!texture.loadFromFile("../plane/resources/plane.png"))
    {
        std::cerr<<"Plane resource Init error!"<<std::endl;
        exit(1);
    }
    setTexture(texture);

}

void Plane::Move(const sf::Vector2f& offset)
{
    if (!CheckCollide(offset)) return;
    this->move(offset);
}

bool Plane::CheckCollide(const sf::Vector2f &offset)
{
    auto afterXPos = getPosition().x + offset.x;
    auto afterYPos = getPosition().y + offset.y;

    return afterXPos >= 0 && afterXPos <= target.getSize().x && afterYPos >= 0 && afterYPos <= target.getSize().y;
}