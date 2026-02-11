#include "Fixed.hpp"
#include <string>
#include <iostream>
#include <cmath>

const int Fixed::_nbits = 8;

Fixed::Fixed() : _integer(0) {
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(const int intval) : _integer(intval << _nbits) {
	std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float fval)
	: _integer(static_cast<int>(roundf(fval * static_cast<float>(1 << _nbits)))) {
	std::cout << "Float constructor called\n";
}

Fixed::Fixed(const Fixed& other) {
	std::cout << "Copy constructor called\n";
	*this = other;
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

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called\n";
	if ( this != &other ) {
		_integer = other._integer;
	}
	return *this;
}

bool	Fixed::operator>(const Fixed& other) const {
	return this->_integer > other._integer;
}

bool	Fixed::operator<(const Fixed& other) const {
	return this->_integer < other._integer;
}

bool	Fixed::operator>=(const Fixed& other) const {
	return this->_integer >= other._integer;
}

bool	Fixed::operator<=(const Fixed& other) const {
	return this->_integer <= other._integer;
}

bool	Fixed::operator==(const Fixed& other) const {
	return this->_integer == other._integer;
}

bool	Fixed::operator!=(const Fixed& other) const {
	return this->_integer != other._integer;
}

Fixed	Fixed::operator+(const Fixed& other) const {
	Fixed result;
	result._integer = this->_integer + other._integer;
	return result;
}

Fixed	Fixed::operator-(const Fixed& other) const {
	Fixed result;
	result._integer = this->_integer - other._integer;
	return result;
}

Fixed	Fixed::operator*(const Fixed& other) const {
	Fixed result;
	int tmp = 1 << _nbits;
	result._integer = (this->_integer * other._integer) / tmp;
	return result;
}

Fixed	Fixed::operator/(const Fixed& other) const {
	Fixed result;
	int tmp = 1 << _nbits;
	result._integer = (this->_integer * tmp) / other._integer;
	return result;
}

Fixed&	Fixed::operator++() {
	_integer += 1;
	return *this;
}

Fixed	Fixed::operator++(int) {
	Fixed cpy = *this;
	++(*this);
	return cpy;
}

Fixed&	Fixed::operator--() {
	_integer -= 1;
	return *this;
}

Fixed	Fixed::operator--(int) {
	Fixed cpy = *this;
	--(*this);
	return cpy;
}

Fixed&			Fixed::min(Fixed& a, Fixed& b) {
	return (a._integer <= b._integer) ? a : b;
}

const Fixed&	Fixed::min(const Fixed& a, const Fixed& b) {
	return (a._integer <= b._integer) ? a : b;
}

Fixed&			Fixed::max(Fixed& a, Fixed& b) {
	return (a._integer >= b._integer) ? a : b;
}

const Fixed&	Fixed::max(const Fixed& a, const Fixed& b) {
	return (a._integer >= b._integer) ? a : b;
}

float Fixed::toFloat(void) const {
	return static_cast<float>(_integer) / static_cast<float>(1 << _nbits);
}

int		Fixed::toInt( void ) const {
	return this->_integer >> _nbits;
}

std::ostream& operator<<(std::ostream& out, const Fixed& value) {
	out << value.toFloat();
	return out;
}
