#ifndef PhoneBook_HPP
# define PhoneBook_HPP


#include "Contact.hpp"

class	PhoneBook {
private:
	Contact	contacts[8];
	int		count;
	int		next;
	int		display_to_real_index(int row0based) const;
	void	print_contact(int i) const;
	void	print_book( void ) const;
public:
	PhoneBook( void );
	void	add( void );
	void	search( void );
};

#endif