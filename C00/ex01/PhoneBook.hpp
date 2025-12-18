#include <iostream>
#include "Contact.hpp"

int	get_input(std::string *str, const std::string& input) {

	bool	only_ws;

	std::cout << input;
	if (!std::getline(std::cin, *str)) {
		std::cout << " getline error " << "\n";
		return 1;
	}
	only_ws = (str->find_first_not_of(" \t\n\r\v\f") == std::string::npos);
	if (only_ws) {
		std::cout << " no correct input " << "\n";
		return 1;
	}
	return 0;
}

int	add_contact(Contact contacts[], int next) {
		std::string	str;

		if (get_input(&str, " First name: ") != 0) { return 1; }
		contacts[next].set_first_name(str);
		std::cout << " just set first name: " << contacts[0].get_first_name() << "\n";

		if (get_input(&str, " Last name: ") != 0) { return 1; }
		contacts[next].set_last_name(str);
		std::cout << " just set last name: " << contacts[0].get_last_name() << "\n";

		if (get_input(&str, " Nickname: ") != 0) { return 1; }
		contacts[next].set_nickname(str);
		std::cout << " just set nickname: " << contacts[0].get_nickname() << "\n";

		if (get_input(&str, " Phone number: ") != 0) { return 1; }
		contacts[next].set_phone_nbr(str);
		std::cout << " just set phone nbr: " << contacts[0].get_phone_nbr() << "\n";

		if (get_input(&str, " Darkest secret: ") != 0) { return 1; }
		contacts[next].set_secret(str);
		std::cout << " just set Darkest secret: " << contacts[0].get_secret() << "\n";
		return 0;
	}

class	PhoneBook {
private:
	Contact	contacts[8];
	int		count;
	int		next;
public:
	PhoneBook( void ) {
		count = 0;
		next = 0;
	}
	void	add( void ) {
		if (add_contact(contacts, next) == 0) {
			if (next < 8) {
				next++;
				count++;
			}
		}
	}
	void	print_book( void ) {
		for(int i = 0; i < count; i++) {
			std::cout << "Contact " << i << ": \n";
			std::cout << " First name: " << contacts[i].get_first_name() << "\n";
			std::cout << " Last name: " << contacts[i].get_last_name() << "\n";
			std::cout << " Nickname: " << contacts[i].get_nickname() << "\n";
			std::cout << " Phone nbr: " << contacts[i].get_phone_nbr() << "\n";
			std::cout << " Darkest secret: " << contacts[i].get_secret() << "\n";
		}
	}
};
