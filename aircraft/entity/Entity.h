#ifndef LEWIS_PLANE_FIGHT_ENTITY
#define LEWIS_PLANE_FIGHT_ENTITY

#include "SceneNode.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// 抽象游戏实体
class Entity : public SceneNode
{
public:
    void setVelocity(sf::Vector2f v);

    void setVelocity(float x, float y);

    sf::Vector2f getVelocity() const;
private:
    sf::Vector2f velocity;
};

#endif