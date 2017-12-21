#include "Entity.h"


void Entity::setVelocity(sf::Vector2f v)
{
    velocity = v;
}

void Entity::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

sf::Vector2f Entity::getVelocity() const
{
    return velocity;
}
