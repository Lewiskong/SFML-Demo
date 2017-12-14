#ifndef LEWIS_SHAPE_H
#define LEWIS_SHAPE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Asterisk : public sf::Shape
{
public:
    explicit  Asterisk(float r):radius(r)
    {
        update();
    }

    void setRadius(float radius)
    {
        this->radius=radius;
        update();
    }

    const float getRadius() const
    {
        return radius;
    }

    virtual std::size_t getPointCount() const
    {
        return 5;
    }

    virtual sf::Vector2f getPoint(size_t index) const
    {
        sf::Vector2f pt;
        static const float pi2 = 3.141592654f*2;

        switch (index)
        {
            case 0:
                pt =sf::Vector2f(0,-radius);
                break;
            case 1:
                pt =sf::Vector2f(float(std::cos(54/360.0f*pi2)*radius),float(sin(54/360.0f*pi2)*radius));
                break;
            case 2:
                pt = sf::Vector2f(-float(std::cos(18/360.0f*pi2)*radius),-float(sin(18/360.0f*pi2)*radius));
                break;
            case 3:
                pt = sf::Vector2f(float(std::cos(18/360.0f*pi2)*radius),-float(sin(18/360.0f*pi2)*radius));
                break;
            case 4:
                pt = sf::Vector2f(-float(std::cos(45/360.0f*pi2)*radius),float(sin(54/360.0f*pi2)*radius));
                break;
            default:
                break;
        }

        return pt;
    }

private:
    float radius;
};


class Ellipse : public sf::Shape
{
public :

    explicit Ellipse(const sf::Vector2f& radius = sf::Vector2f(0, 0)) :
            m_radius(radius)
    {
        update();
    }

    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }

    virtual size_t getPointCount() const
    {
        return 30; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

private :

    sf::Vector2f m_radius;
};


#endif