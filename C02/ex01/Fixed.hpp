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
	Fixed& operator=(const Fixed& other);
	~Fixed();

	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
	float	toFloat( void ) const;
	int		toInt( void ) const;
};

std::ostream& operator<<(std::ostream& out, const Fixed& value);

#endif
