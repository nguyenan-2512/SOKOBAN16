#pragma once
#include "Point.h"
#include <vector>

// Struct luu trang thai mot nuoc di de phuc vu Undo
struct MoveState {
    Point playerPosition;
    std::vector<Point> boxPositions;

    MoveState() {}

    MoveState(const Point& playerPos, const std::vector<Point>& boxPos)
        : playerPosition(playerPos), boxPositions(boxPos) {
    }
};