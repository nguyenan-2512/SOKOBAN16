#pragma once	
class Point {
private:
	int x;
	int y;
public:
	Point(int = 0, int = 0);
	~Point();
	int getX() const;
	int getY() const;
	void setX(int);
	void setY(int);
	void setXY(int, int);
	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;
};

