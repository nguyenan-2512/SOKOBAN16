#pragma once
#include "GameObject.h"

class Box : public GameObject {
public:
    Box(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
}; 
