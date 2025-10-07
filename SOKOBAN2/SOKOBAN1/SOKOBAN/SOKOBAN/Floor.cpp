#include "Floor.h"

Floor::Floor(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Floor::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}