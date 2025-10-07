#include "Player.h"

Player::Player(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
