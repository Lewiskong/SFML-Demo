#ifndef LEWIS_PLANE_FIGHT_ENTITY
#define LEWIS_PLANE_FIGHT_ENTITY

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Entity
{
public:
    void setVelocity(sf::Vector2f v);

    void setVelocity(float x, float y);

    sf::Vector2f getVelocity() const;
private:
    sf::Vector2f velocity;
};

#endif