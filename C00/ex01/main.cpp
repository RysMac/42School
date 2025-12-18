#include <iostream>
#include "PhoneBook.hpp"



int	main() {

	PhoneBook book;

	book.add();
	book.print_book();

	std::cout << "hello PhoneBook \n";

	return 0;
}
