#include "Fixed.hpp"
#include "Point.hpp"

static Fixed orient(Point const& a, Point const& b, Point const& p) {
	Fixed const dx1 = b.getX() - a.getX();
	Fixed const dy1 = b.getY() - a.getY();
	Fixed const dx2 = p.getX() - a.getX();
	Fixed const dy2 = p.getY() - a.getY();
	return (dx1 * dy2) - (dy1 * dx2);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point) {

	Fixed const area = orient(a, b, c);
	if (area == Fixed(0))
		return false;

	Fixed const s1 = orient(a, b, point);
	Fixed const s2 = orient(b, c, point);
	Fixed const s3 = orient(c, a, point);

	// On an edge or vertex => false (strictly inside only)
	if (s1 == Fixed(0) || s2 == Fixed(0) || s3 == Fixed(0))
		return false;

	// Inside if all have same sign (works for CW or CCW ordering)
	return ((s1 > Fixed(0) && s2 > Fixed(0) && s3 > Fixed(0)) ||
			(s1 < Fixed(0) && s2 < Fixed(0) && s3 < Fixed(0)));
}
