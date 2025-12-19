
#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : count(0), next(0) {}

static int	get_input(std::string *str, const std::string& input) {

	bool	only_ws;

	std::cout << input << std::flush;
	if (!std::getline(std::cin, *str)) {
		std::cout << " getline error " << "\n";
		return 1;
	}
	only_ws = (str->find_first_not_of(" \t\n\r\v\f") == std::string::npos);
	if (only_ws) {
		std::cout << " wrong input " << "\n";
		return 1;
	}
	return 0;
}

static int	add_contact(Contact contacts[], int next) {
		std::string	str[5];

		if (get_input(&str[0], " First name: ") != 0) {
			std::cout << "Contact not saved. \n";
			return 1;
		}
		if (get_input(&str[1], " Last name: ") != 0) {
			std::cout << "Contact not saved. \n";
			return 1;
		}
		if (get_input(&str[2], " Nickname: ") != 0) {
			std::cout << "Contact not saved. \n";
			return 1;
		}
		if (get_input(&str[3], " Phone number: ") != 0) {
			std::cout << "Contact not saved. \n";
			return 1;
		}
		if (get_input(&str[4], " Darkest secret: ") != 0) {
			std::cout << "Contact not saved. \n";
			return 1;
		}
		contacts[next].set_first_name(str[0]);
		contacts[next].set_last_name(str[1]);
		contacts[next].set_nickname(str[2]);
		contacts[next].set_phone_nbr(str[3]);
		contacts[next].set_secret(str[4]);
		return 0;
	}

	void	PhoneBook::add( void ) {
		if (add_contact(contacts, next) == 0) {
			next++;
			if (next > 7) { next = 0; }
			if (count < 8) { count++; }
		}
	}

	void	PhoneBook::print_book( void ) {
		for(int i = 0; i < count; i++) {
			std::cout << "Contact " << i+1 << ": \n";
			std::cout << " First name: " << contacts[i].get_first_name() << "\n";
			std::cout << " Last name: " << contacts[i].get_last_name() << "\n";
			std::cout << " Nickname: " << contacts[i].get_nickname() << "\n";
			std::cout << " Phone nbr: " << contacts[i].get_phone_nbr() << "\n";
			std::cout << " Darkest secret: " << contacts[i].get_secret() << "\n";
		}
	}
