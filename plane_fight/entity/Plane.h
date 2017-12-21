#ifndef LEWIS_PLANE_FIGHT_PLANE_H
#define LEWIS_PLANE_FIGHT_PLANE_H

#include "Entity.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Plane: public Entity
{
public:
    enum Type {
        DaHuangFeng,
        LeiDian
    };

public:
    explicit Plane(Type type);

private:
    Type type;
};


#endif