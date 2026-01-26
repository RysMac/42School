#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
private:
	Fixed const	x;
	Fixed const	y;
public:
	Point();
	Point(const float a, const float b);
	Point(const Fixed& p1, const Fixed& p2);
	Point(const Point& other);
	~Point();

	Point&	operator=(const Point& other); // copy ctr

	Fixed const& getX() const;
	Fixed const& getY() const;

};

Fixed	cross(const Point& p1, const Point& p2);
bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif
