#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

int	main() {

	Point	p1(2.455555,2.256666);
	Point	p2(6, 9);

	std::cout << "Point p1 = " << p1.getX() << std::endl;
	std::cout << "Point p2 = " << p1.getY() << std::endl;

	std::cout << cross(p1, p2) << std::endl;
	std::cout << bsp(p1, p2, p1, p2) << std::endl;
	return 0;
}
