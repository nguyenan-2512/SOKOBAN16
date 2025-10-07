#pragma once
#include "GameObject.h"

// L?p Goal ??i di?n cho v? trí ?ích (d?u X) mà Box c?n ???c ??y ??n
class Goal : public GameObject {
public:
    Goal(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};
