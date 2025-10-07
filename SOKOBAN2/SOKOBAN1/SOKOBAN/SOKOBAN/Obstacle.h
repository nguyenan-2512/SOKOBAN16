#pragma once
#include "GameObject.h"

// L?p Obstacle ??i di?n cho v?t c?n - không th? ??y ???c
// Khác v?i Wall (t??ng) và Box (thùng có th? ??y)
class Obstacle : public GameObject {
public:
    Obstacle(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};