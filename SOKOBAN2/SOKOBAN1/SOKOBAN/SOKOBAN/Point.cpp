#include "Point.h"
#include <iostream>
using namespace std;

Point::Point(int x, int y) : x(x), y(y) {}
Point::~Point() {}
int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}
void Point::setX(int x) {
	this->x = x;
}
void Point::setY(int y) {
	this->y = y;
}
void Point::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}
bool Point::operator==(const Point& other) const {
	return (x == other.x && y == other.y);
}
bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}

