#include "Box.h"

Box::Box(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Box::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}