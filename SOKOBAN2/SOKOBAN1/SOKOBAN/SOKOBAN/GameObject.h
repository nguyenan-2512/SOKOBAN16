#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    Point position;
    sf::Sprite sprite;
    int tileSize;
public:
    GameObject(int x, int y, int tileSize);
    virtual ~GameObject() = default;
    Point getPosition() const;
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    void setTexture(const sf::Texture& texture);
    virtual void draw(sf::RenderWindow& window) = 0;
};