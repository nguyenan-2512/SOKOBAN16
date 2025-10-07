
#pragma once
#include "GameObject.h"

class Floor : public GameObject {
public:
    Floor(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};