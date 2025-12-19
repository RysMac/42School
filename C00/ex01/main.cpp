#include <iostream>
#include "PhoneBook.hpp"


int	main() {

	PhoneBook	book;
	std::string	str;

	while (1) {
		if (!std::getline(std::cin, str)) {
			std::cout << " getline error " << "\n";
			return 1;
		}
		if (str == "ADD") {
			book.add();
		} else if (str == "EXIT")
		{
			break ;
		}
	}
	book.print_book();
	std::cout << "hello PhoneBook \n";

	return 0;
}
