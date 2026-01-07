#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name): name(name), weapon(NULL) {}

void	HumanB::attack( void ) const {
	if (weapon == NULL)
		std::cout << name << " cannot attack, is unarmed \n";
	else
		std::cout << name << " attacks with their " << weapon->getType() << "\n";
}

void	HumanB::setWeapon(Weapon* weapon) {
	this->weapon = weapon;
}
