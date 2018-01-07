#include "Plane.h"

Plane::Plane(Plane::Type type, const ResourceHolder &holder) : type(type), sprite(holder.GetTexture(toResourceId(type)))
{

}

void Plane::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite,states);
}

ResourceHolder::ResourceId Plane::toResourceId(Plane::Type type) {
    switch (type)
    {
        case Plane::Type::DaHuangFeng:
            return ResourceHolder::ResourceId::RESOURCE_DA_HUANG_FENG;
        case Plane::Type::LeiDian:
            return ResourceHolder::ResourceId::RESOURCE_LEI_DIAN;
        default:
            exit(1);
    }
}
