#include "Fixed.hpp"
#include <iostream>

int	main() {

	Fixed		a;
	Fixed const b( 10 );
	Fixed const c( 42.42f );
	Fixed const d( b );

	a = Fixed( 1234.4321f );

	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;

	std::cout << "is 3 gt 1: " << (Fixed(3) > Fixed(1)) << std::endl;

	std::cout << "sum works? " << (Fixed(3) + Fixed(1)) << std::endl;
	std::cout << "subs works? " << (Fixed(3) - Fixed(1)) << std::endl;
	std::cout << "multi works? " << (Fixed(3) * Fixed(1)) << std::endl;
	std::cout << "div works? " << (Fixed(3) / Fixed(3.001f)) << std::endl;

	std::cout << "++pre " << ++Fixed(3) << std::endl;
	std::cout << "--pre " << --Fixed(3) << std::endl;

	Fixed		aa;
	Fixed const	bb( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << aa << std::endl;
	std::cout << ++aa << std::endl;
	std::cout << aa << std::endl;
	std::cout << aa++ << std::endl;
	std::cout << aa << std::endl;

	std::cout << bb << std::endl;

	std::cout << Fixed::max( aa, bb) << std::endl;

	return 0;
}
