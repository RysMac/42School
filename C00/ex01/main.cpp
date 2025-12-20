#include <iostream>
#include "PhoneBook.hpp"

int	main( void ) {

	PhoneBook	book;
	std::string	str;

	while (1) {
		std::cout << "Use one of: ADD | SEARCH | EXIT \n";
		if (!std::getline(std::cin, str)) {
			std::cout << " getline error " << "\n";
			return 1;
		}
		if (str == "ADD") {
			book.add();
		} else if (str == "SEARCH") {
			book.search();
		} else if (str == "EXIT") {
			break ;
		}
	}
	return 0;
}
