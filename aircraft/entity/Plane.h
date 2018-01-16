#ifndef LEWIS_PLANE_FIGHT_PLANE_H
#define LEWIS_PLANE_FIGHT_PLANE_H

#include "Entity.h"
#include "../ResourceHolder.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Plane: public Entity
{
public:
    enum Type {
        DaHuangFeng,
        LeiDian,
        EternalTranquil
    };

public:
    explicit Plane(Type type,const ResourceHolder &holder);

private:
    void drawCurrent(RenderTarget &target, sf::RenderStates states) const override;

    ResourceHolder::ResourceId toResourceId(Plane::Type type);


private:
    Type type;
    sf::Sprite sprite;
};


#endif