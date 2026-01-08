#include <iostream>
#include "Zombie.hpp"

Zombie::Zombie(std::string name) : name(name) {}

Zombie::Zombie( void ) {}

Zombie::~Zombie( void ) {
	std::cout << name << " is dead\n";
}

void	Zombie::set_name( std::string name) {
	this->name = name;
}

void	Zombie::announce( void ) {
	std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}