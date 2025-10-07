#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map(const std::string& filename, int tileSize) : tileSize(tileSize), player(nullptr) {
    // Load tất cả textures
    if (!wallTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\wall.png")) {
        std::cerr << "Failed to load wall texture!" << std::endl;
    }
    if (!playerTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\worker.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
    }
    if (!floorTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\floor.png")) {
        std::cerr << "Failed to load floor texture!" << std::endl;
    }
    if (!boxTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\box.png")) {
        std::cerr << "Failed to load box texture!" << std::endl;
    }

    // ===== THÊM ẢNH Ở ĐÂY =====
    if (!goalTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\dock.png")) {
    std::cerr << "Failed to load goal texture!" << std::endl;
}


    if (!obstacleTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\wall.png")) {
std::cerr << "Failed to load obstacle texture!" << std::endl;
    }

    // Đọc file map
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file map: " << filename << std::endl;
        return;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];

            // # = Tường (Wall)
            if (c == '#') {
                walls.emplace_back(x, y, tileSize);
                walls.back().setTexture(wallTexture);
            }
            // @ = Nhân vật (Player)
            else if (c == '@') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                player = new Player(x, y, tileSize);
                player->setTexture(playerTexture);
            }
            // $ = Thùng (Box - có thể đẩy)
            else if (c == '$') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                boxes.emplace_back(x, y, tileSize);
                boxes.back().setTexture(boxTexture);
            }
            // X = Vị trí đích (Goal)
            else if (c == 'X' || c == 'x') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
            }
            // O = Vật cản (Obstacle - không thể đẩy)
            else if (c == 'O' || c == 'o') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                obstacles.emplace_back(x, y, tileSize);
                obstacles.back().setTexture(obstacleTexture);
            }
            // + = Player đứng trên Goal
            else if (c == '+') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
                player = new Player(x, y, tileSize);
                player->setTexture(playerTexture);
            }
            // * = Box đứng trên Goal
            else if (c == '*') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
                boxes.emplace_back(x, y, tileSize);
                boxes.back().setTexture(boxTexture);
            }
            // . hoặc space = Sàn trống (Floor)
            else if (c == '.' || c == ' ') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
            }
        }
        y++;
    }
    file.close();
}

Map::~Map() {
    delete player;
}

void Map::draw(sf::RenderWindow& window) {
    // Vẽ theo thứ tự: Floor -> Goal -> Obstacle -> Wall -> Box -> Player
    for (auto& floor : floors) {
        floor.draw(window);
    }
    for (auto& goal : goals) {
        goal.draw(window);
    }
    for (auto& obstacle : obstacles) {
        obstacle.draw(window);
    }
    for (auto& wall : walls) {
        wall.draw(window);
    }
    for (auto& box : boxes) {
        box.draw(window);
    }
    if (player) player->draw(window);
}

Player* Map::getPlayer() {
    return player;
}

bool Map::isWall(int x, int y) const {
    return std::any_of(walls.begin(), walls.end(),
        [x, y](const Wall& wall) {
            return wall.getX() == x && wall.getY() == y;
        });
}

bool Map::isBox(int x, int y) const {
    return std::any_of(boxes.begin(), boxes.end(),
        [x, y](const Box& box) {
            return box.getX() == x && box.getY() == y;
        });
}

// Kiểm tra có vật cản tại vị trí (x, y) không
bool Map::isObstacle(int x, int y) const {
    return std::any_of(obstacles.begin(), obstacles.end(),
        [x, y](const Obstacle& obstacle) {
            return obstacle.getX() == x && obstacle.getY() == y;
        });
}

Box* Map::getBoxAt(int x, int y) {
    for (auto& box : boxes) {
        if (box.getX() == x && box.getY() == y) {
            return &box;
        }
    }
    return nullptr;
}

bool Map::isValidMove(int x, int y) {
    if (isWall(x, y) || isObstacle(x, y)) {  // Thêm kiểm tra Obstacle
        return false;
    }
    return true;
}

bool Map::moveBox(Box* box, int dx, int dy) {
    int newX = box->getX() + dx;
    int newY = box->getY() + dy;

    // Box không thể đẩy vào Wall, Obstacle hoặc Box khác
    if (!isWall(newX, newY) && !isObstacle(newX, newY) && !isBox(newX, newY)) {
        box->setPosition(newX, newY);
        return true;
    }
    return false;
}

bool Map::tryMovePlayer(int dx, int dy) {
    if (!player) return false;

    int newX = player->getX() + dx;
    int newY = player->getY() + dy;

    // Không thể đi vào Wall hoặc Obstacle
    if (isWall(newX, newY) || isObstacle(newX, newY)) {
        return false;
    }

    // Nếu có Box, thử đẩy nó
    Box* box = getBoxAt(newX, newY);
    if (box) {
        if (!moveBox(box, dx, dy)) {
            return false;
        }
    }

    // LUU TRANG THAI TRUOC KHI DI CHUYEN
    saveState();

    player->setPosition(newX, newY);
    return true;
}


// Kiểm tra thắng game: tất cả Box phải ở trên Goal
bool Map::checkWin() const {
    // Debug: In ra số lượng box và goal
    std::cout << "=== KIEM TRA THANG ===" << std::endl;
    std::cout << "So box: " << boxes.size() << std::endl;
    std::cout << "So goal: " << goals.size() << std::endl;

    // Nếu không có box hoặc goal, chưa thắng
    if (boxes.size() == 0 || goals.size() == 0) {
        std::cout << "Chua co box hoac goal!" << std::endl;
        return false;
    }

    // Nếu số box khác số goal, chưa thắng
    if (boxes.size() != goals.size()) {
        std::cout << "So box khac so goal!" << std::endl;
        return false;
    }

    // Kiểm tra từng box xem có nằm trên goal không
    int boxOnGoal = 0;
    for (const auto& box : boxes) {
        bool onGoal = false;
        std::cout << "Box o vi tri: (" << box.getX() << ", " << box.getY() << ")" << std::endl;

        for (const auto& goal : goals) {
            std::cout << "  - Kiem tra goal o: (" << goal.getX() << ", " << goal.getY() << ")" << std::endl;

            if (box.getX() == goal.getX() && box.getY() == goal.getY()) {
                onGoal = true;
                boxOnGoal++;
                std::cout << "  >>> Box NAM TREN goal!" << std::endl;
                break;
            }
        }

        if (!onGoal) {
            std::cout << "  >>> Box CHUA nam tren goal nao!" << std::endl;
            return false;
        }
    }

    std::cout << "TAT CA " << boxOnGoal << " box deu nam tren goal! THANG!" << std::endl;
    return true;
}


// ========== CAC HAM UNDO ==========

// ========== CAC HAM UNDO ==========

void Map::saveState() {
    MoveState state = getCurrentState();
    moveHistory.push(state);
}

MoveState Map::getCurrentState() const {
    Point playerPos = player->getPosition();
    std::vector<Point> boxPos;

    for (const auto& box : boxes) {
        boxPos.push_back(box.getPosition());
    }

    return MoveState(playerPos, boxPos);
}

void Map::restoreState(const MoveState& state) {
    player->setPosition(state.playerPosition.getX(), state.playerPosition.getY());

    for (size_t i = 0; i < boxes.size() && i < state.boxPositions.size(); i++) {
        boxes[i].setPosition(state.boxPositions[i].getX(), state.boxPositions[i].getY());
    }
}

void Map::undo() {
    if (moveHistory.empty()) {
        std::cout << "Khong co nuoc di nao de undo!" << std::endl;
        return;
    }

    MoveState previousState = moveHistory.top();
    moveHistory.pop();

    restoreState(previousState);

    std::cout << "Da undo! Con lai " << moveHistory.size() << " nuoc di trong lich su." << std::endl;
}

int Map::getMoveCount() const {
    return (int)moveHistory.size();
}