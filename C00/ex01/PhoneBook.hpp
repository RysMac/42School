#include <iostream>
#include "Contact.hpp"

class	PhoneBook {
private:
	Contact	contacts[8];
	int		count;
	int		next;
public:
	PhoneBook( void );
	void	add( void );
	void	print_book( void );
};
