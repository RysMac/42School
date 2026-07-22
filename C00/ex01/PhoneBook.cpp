
#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

PhoneBook::PhoneBook( void ) : count(0), next(0) {}

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

static int	add_contact(Contact contacts[], int idx) {
	std::string	str[5];

	if (get_input(&str[0], " First name: ") != 0) { std::cout << "Contact not saved. \n"; return 1; }
	if (get_input(&str[1], " Last name: ") != 0) { std::cout << "Contact not saved. \n"; return 1; }
	if (get_input(&str[2], " Nickname: ") != 0) { std::cout << "Contact not saved. \n"; return 1; }
	if (get_input(&str[3], " Phone number: ") != 0) { std::cout << "Contact not saved. \n"; return 1; }
	if (get_input(&str[4], " Darkest secret: ") != 0) { std::cout << "Contact not saved. \n"; return 1; }
	
	contacts[idx].set_first_name(str[0]);
	contacts[idx].set_last_name(str[1]);
	contacts[idx].set_nickname(str[2]);
	contacts[idx].set_phone_nbr(str[3]);
	contacts[idx].set_secret(str[4]);
	return 0;
}

void	PhoneBook::add( void ) {
	if (add_contact(contacts, next) == 0) {
		next = (next + 1) % 8;
		if (count < 8) { count++; }
	}
}

static std::string format_col(const std::string& s) {
	if (s.length() > 10)
		return s.substr(0, 9) + ".";
	return s;
}

static bool	is_number(const std::string &s) {
	if (s.empty())
		return false;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return false;
	}
	return true;
}

int PhoneBook::display_to_real_index(int row0based) const {
	if (count < 8)
		return row0based;
	return (next + row0based) % 8;
}

void PhoneBook::print_book(void) const {
	std::cout << std::right;
	std::cout << std::setw(10) << "index" << '|'
			  << std::setw(10) << "first name" << '|'
			  << std::setw(10) << "last name" << '|'
			  << std::setw(10) << "nickname" << "\n";

	for (int row = 0; row < count; ++row) {
		int i = display_to_real_index(row);
		std::cout << std::setw(10) << (i + 1) << '|'
				<< std::setw(10) << format_col(contacts[i].get_first_name()) << '|'
				<< std::setw(10) << format_col(contacts[i].get_last_name()) << '|'
				<< std::setw(10) << format_col(contacts[i].get_nickname()) << "\n";
	}
}

void PhoneBook::print_contact(int i) const
{
	std::cout << "First name: " << contacts[i].get_first_name() << "\n";
	std::cout << "Last name: " << contacts[i].get_last_name() << "\n";
	std::cout << "Nickname: " << contacts[i].get_nickname() << "\n";
	std::cout << "Phone number: " << contacts[i].get_phone_nbr() << "\n";
	std::cout << "Darkest secret: " << contacts[i].get_secret() << "\n";
}

void	PhoneBook::search( void ) {
	if (count == 0) {
		std::cout << "Phone book is empty \n";
		return;
	}
		print_book();
		std::string str;
		
		std::cout << "INDEX (1-" << count <<"): " << std::flush;
		if (!std::getline(std::cin, str)) {
			std::cout << " getline error " << "\n";
			return;
		}
		if (!is_number(str)) {
			std::cout << "Invalid index\n";
			return;
		}
		int idx = std::atoi(str.c_str());
		if (idx < 1 || idx > count) {
			std::cout << "Invalid index\n";
			return;
		}
		int row0based = idx - 1;
		int realIndex = display_to_real_index(row0based);
		print_contact(realIndex);
}