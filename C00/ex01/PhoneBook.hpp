// if ndef stuff...


#include "Contact.hpp"

class	PhoneBook {
private:
	Contact	contacts[8];
	int		count;
	int		next;
	void	print_contact(int i) const;
	void	print_book( void ) const;
public:
	PhoneBook( void );
	void	add( void );
	void	search( void );
};
