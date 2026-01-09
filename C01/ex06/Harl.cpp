#include "Harl.hpp"
#include <iostream>
#include <string>

void	Harl::debug( void ) const {
	std::cout << "DEBUG level: ";
	std::cout << "I love having extra bacon for my ";
	std::cout << "7XL-double-cheese-triple-pickle-special-ketchup burger. ";
	std::cout << "I really do!\n";
}

void	Harl::info( void ) const {
	std::cout << "INFO level: ";
	std::cout << "I cannot believe adding extra bacon costs more money. ";
	std::cout << "You didn't put enough bacon in my burger! ";
	std::cout << "If you did, I wouldn't be asking for more!\n";
}

void	Harl::warning( void ) const {
	std::cout << "WARNING level: ";
	std::cout << "I think I deserve to have some extra bacon for free. ";
	std::cout << "I've been coming for years, whereas you started working here just last month.\n";
}

void	Harl::error( void ) const {
	std::cout << "ERROR level: ";
	std::cout << "This is unacceptable! I want to speak to the manager now.\n";
}

int	Harl::levelToIndex(const std::string& level) const {
	static const std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
	const std::size_t n = sizeof(levels) / sizeof(levels[0]);

	for (std::size_t i = 0; i < n; ++i) {
		if (level == levels[i])
			return static_cast<int>(i);
	}
	return -1;
}

void	Harl::complain(const std::string& level) const {
 	static int l =  levelToIndex(level);
	static void (Harl::*actions[])( void ) const = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
	int	n_actions = static_cast<int>(sizeof(actions) / sizeof(actions[0]));

	if (l < 0 || l >= n_actions) {
		std::cout << "Unrecognized level\n";
		return;
	}
	(this->*actions[l])();
}


