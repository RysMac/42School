#include "Harl.hpp"
#include <iostream>
#include <string>

void	Harl::debug( void ) {
	std::cout << "DEBUG level: ";
	std::cout << "I love having extra bacon for my ";
	std::cout << "7XL-double-cheese-triple-pickle-special-ketchup burger. ";
	std::cout << "I really do!\n";
}

void	Harl::info( void ) {
	std::cout << "INFO level: ";
	std::cout << "I cannot believe adding extra bacon costs more money. ";
	std::cout << "You didn’t put enough bacon in my burger! ";
	std::cout << "If you did, I wouldn’t be asking for more!\n";
}

void	Harl::warning( void ) {
	std::cout << "WARNING level: ";
	std::cout << "I think I deserve to have some extra bacon for free. ";
	std::cout << "I’ve been coming for years, whereas you started working here just last month.\n";
}

void	Harl::error( void ) {
	std::cout << "ERROR level: ";
	std::cout << "This is unacceptable! I want to speak to the manager now.\n";
}

void	Harl::complain( std::string level) {
	static const std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
	static void (Harl::*actions[])( void ) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
	const std::size_t n = sizeof(levels)/sizeof(levels[0]);
	for (std::size_t i = 0; i < n; ++i) {
		if (level == levels[i]) {
			(this->*actions[i])();
			return;
		}
	}
	std::cout << "Unrecognized level\n";
}
