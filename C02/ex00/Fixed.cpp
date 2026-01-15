#include "Fixed.hpp"
#include <string>
#include <iostream>

const int Fixed::_nbits = 8;

Fixed::Fixed() : _integer(0) {
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(const Fixed& other) {
	std::cout << "Copy constructor called\n";
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called\n";
	if ( this != &other ) {
		_integer = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called\n";
}

int		Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called\n";
	return this->_integer;
}

void	Fixed::setRawBits( int const raw ) {
	std::cout << "setRawBits member function called\n";
	this->_integer = raw;
}
