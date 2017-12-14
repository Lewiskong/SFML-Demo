#ifndef LEWIS_GOBANG_H
#define LEWIS_GOBANG_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Gobang
{
public:
    explicit Gobang(sf::RenderWindow &wd,size_t sz=16, float per=1.0f):window(wd),size(sz),percent(per){}

    void InitBoard();
private:
    sf::RenderWindow &window;
    size_t size;
    float percent;

};



#endif