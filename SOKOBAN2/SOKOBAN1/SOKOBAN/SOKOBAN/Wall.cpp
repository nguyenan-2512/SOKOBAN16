#include "Wall.h"

Wall::Wall(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Wall::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}