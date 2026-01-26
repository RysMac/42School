#include "Fixed.hpp"
#include "Point.hpp"

Point::Point() : x(0), y(0) {};

Point::Point(const float a, const float b) : x(a), y(b) {};

Point::Point(const Point& other) : x(other.x), y(other.y) {};

Point::Point(const Fixed& p1, const Fixed& p2) : x(p1), y(p2) {};

Point::~Point() {};

Point&	Point::operator=(const Point& other) {
	(void)other;
	return *this;
}

Fixed const&	Point::getX() const {
	return (this->x);
}

Fixed const&	Point::getY() const {
	return (this->y);
}
