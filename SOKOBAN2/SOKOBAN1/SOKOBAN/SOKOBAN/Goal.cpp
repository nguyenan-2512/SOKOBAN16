#include "Goal.h"

Goal::Goal(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Goal::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}