#include "Fixed.hpp"
#include "Point.hpp"

Fixed	cross(const Point& p1, const Point& p2)
{
	return p1.getX() * p2.getY() - p1.getY() * p2.getX();
}

Point	dxdy(Point const& a, Point const& b) {
	// Fixed dx = a.getX() - b.getX();
	// Fixed dy = a.getY() - b.getY();
	return Point(a.getX() - b.getX(), a.getY() - b.getY());
}

bool	bsp(Point const a, Point const b, Point const c, Point const point) {

	Fixed s1 = cross(dxdy(b, a), dxdy(point, a));
	Fixed s2 = cross(dxdy(c, b), dxdy(point, b));
	Fixed s3 = cross(dxdy(a, c), dxdy(point, c));

	return (cross(a, b) > 0);
}
