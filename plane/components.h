#ifndef LEWIS_COMPONENT_H
#define LEWIS_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>



class Plane : public sf::Sprite
{
public:
    Plane(sf::RenderTarget &window);
    void Move(const sf::Vector2f& offset);

private:
    bool CheckCollide(const sf::Vector2f &offset);

private:
    sf::Texture texture;
    sf::RenderTarget &target;

};


class Bullet : public sf::CircleShape
{
public:
    Bullet(const sf::Vector2f &pos, sf::Transformable &target,sf::RenderTarget *renderTarget, float radius = 50.f, float sp = 200.f);


    void Move(const sf::Time &time);
    bool isOut();
    bool isCollide(const Plane& plane);

    Bullet(const Bullet &bullet) = default;

private:
    float speed;

    sf::Vector2f direction;
    sf::RenderTarget *window;
};



#endif