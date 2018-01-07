#ifndef LEWIS_WORLD_H
#define LEWIS_WORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class World:public sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();

private:
    void loadTextures();
    void buildScene();

private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderWindow &window;
    sf::View view;
//    TextureHolder textures;
//    SceneNode sceneGraph;



};

#endif