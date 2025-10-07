#pragma once
#include <vector>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Player.h"
#include "Floor.h"
#include "Box.h"
#include "Goal.h"
#include "Obstacle.h"
#include "MoveState.h"

class Map {
private:
    std::vector<Wall> walls;
    std::vector<Floor> floors;
    std::vector<Box> boxes;
    std::vector<Goal> goals;
    std::vector<Obstacle> obstacles;
    Player* player;
    int tileSize;

    std::stack<MoveState> moveHistory;  // Doi thanh MoveState

    sf::Texture wallTexture;
    sf::Texture playerTexture;
    sf::Texture floorTexture;
    sf::Texture boxTexture;
    sf::Texture goalTexture;
    sf::Texture obstacleTexture;

public:
    Map(const std::string& filename, int tileSize = 32);
    ~Map();

    void draw(sf::RenderWindow& window);
    Player* getPlayer();

    bool isWall(int x, int y) const;
    bool isBox(int x, int y) const;
    bool isObstacle(int x, int y) const;
    Box* getBoxAt(int x, int y);
    bool isValidMove(int x, int y);
    bool moveBox(Box* box, int dx, int dy);
    bool tryMovePlayer(int dx, int dy);
    bool checkWin() const;

    void undo();
    int getMoveCount() const;

private:
    void saveState();
    MoveState getCurrentState() const;  // Doi thanh MoveState
    void restoreState(const MoveState& state);  // Doi thanh MoveState
};