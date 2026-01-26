#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

int	main() {

	Point	p1(-1.5, -1.5);
	Point	p2(1.5, -1.5);
	Point	p3(0.0, 1.5);

	Point	point1(0., 0.); // inside
	Point	point2(10., 0.); // outside
	Point	point3(0, 1.5); // on corner

	std::cout << "inside?: " << bsp(p1, p2, p3, point1) << std::endl;
	std::cout << "outside?: " << bsp(p1, p2, p3, point2) << std::endl;
	std::cout << "on a vertex: " << bsp(p1, p2, p3, point3) << std::endl;
	return 0;
}
