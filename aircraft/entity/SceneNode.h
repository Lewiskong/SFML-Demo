#ifndef LEWIS_SCENE_NODE_H
#define LEWIS_SCENE_NODE_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class SceneNode:public sf::Transformable,sf::Drawable,sf::NonCopyable
{
public:
    using Ptr = std::unique_ptr<SceneNode>;

public:
    SceneNode();

    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode &node);

private:
    virtual void draw(RenderTarget &target, sf::RenderStates states) const override;
    virtual void drawCurrent(RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<Ptr> children;
    SceneNode *parent;
};


#endif