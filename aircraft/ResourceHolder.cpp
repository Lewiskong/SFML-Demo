#include "ResourceHolder.h"

ResourceHolder::ResourceHolder()
{

}

void ResourceHolder::LoadTexture(ResourceHolder::ResourceId id, const std::string &name) {
    std::unique_ptr<sf::Texture> res(new sf::Texture);

    if (!res->loadFromFile(name))
    {
        throw std::runtime_error("fail to load " + name );
    }

    auto inserted = textures.insert(std::make_pair(id,std::move(res)));
    if (!inserted.second)
    {
        throw std::runtime_error("fail to insert " + name );
    }
}

sf::Texture &ResourceHolder::GetTexture(ResourceHolder::ResourceId id) {
    auto it = textures.find(id);
    if (it == textures.end())
    {
        throw std::runtime_error("resources incomplete!");
    }
    return *it->second;
}

sf::Texture &ResourceHolder::GetTexture(ResourceHolder::ResourceId id) const
{
    auto it = textures.find(id);
    if (it == textures.end())
    {
        throw std::runtime_error("resources incomplete!");
    }
    return *it->second;
}
