#ifndef FIXED_HPP
#define FIXED_HPP
#include <ostream>

class Fixed {
private:
	int					_integer;
	static const int	_nbits;
public:
	Fixed();
	Fixed(const int intval);
	Fixed(const float fval);
	Fixed(const Fixed& other);

	Fixed&	operator=(const Fixed& other);
	bool	operator>(const Fixed& other) const;
	bool	operator<(const Fixed& other) const;
	bool	operator>=(const Fixed& other) const;
	bool	operator<=(const Fixed& other) const;
	bool	operator==(const Fixed& other) const;
	bool	operator!=(const Fixed& other) const;

	Fixed	operator+(const Fixed& other) const;
	Fixed	operator-(const Fixed& other) const;
	Fixed	operator*(const Fixed& other) const;
	Fixed	operator/(const Fixed& other) const;

	Fixed&	operator++();
	Fixed	operator++(int);
	Fixed&	operator--();
	Fixed	operator--(int);
	~Fixed();

	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
	float	toFloat( void ) const;
	int		toInt( void ) const;

	static Fixed&		min(Fixed& a, Fixed& b);
	static const Fixed&	min(const Fixed& a, const Fixed& b);
	static Fixed&		max(Fixed& a, Fixed& b);
	static const Fixed&	max(const Fixed& a, const Fixed& b);
};

std::ostream& operator<<(std::ostream& out, const Fixed& value);

#endif
