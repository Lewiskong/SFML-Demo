#ifndef LEWIS_RESOURCE_HOLDER_H
#define LEWIS_RESOURCE_HOLDER_H

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceHolder
{
public:
    ResourceHolder();
    enum class ResourceId
    {
        RESOURCE_DA_HUANG_FENG,
        RESOURCE_LEI_DIAN
    };

    void LoadTexture(ResourceHolder::ResourceId id , const std::string &name);

    sf::Texture& GetTexture(ResourceHolder::ResourceId id);

    sf::Texture &GetTexture(ResourceHolder::ResourceId id) const;

private:
    std::map<ResourceHolder::ResourceId , std::unique_ptr<sf::Texture>> textures;
};

#endif
