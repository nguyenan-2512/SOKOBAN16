#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
    Player(int x = 0, int y = 0, int tileSize = 40);
    void draw(sf::RenderWindow& window) override;
};