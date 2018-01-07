#include "SceneNode.h"
#include <cassert>

SceneNode::SceneNode()
{

}

void SceneNode::attachChild(SceneNode::Ptr child)
{
    child->parent=this;
    children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node) {
    auto found = std::find_if(children.begin(),children.end(),
        [&](Ptr &p)->bool{return p.get()==&node;});

    assert(found != children.end());

    Ptr result = std::move(*found);
    result->parent= nullptr;
    children.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    drawCurrent(target, states);
    for (auto it = children.begin(); it != children.end(); it++)
    {
        (*it)->draw(target,states);
    }
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}
