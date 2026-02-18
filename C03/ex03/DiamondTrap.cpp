#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(const std::string& name)
	: ClapTrap(name + "_clap_name"),
	  ScavTrap(name),
	  FragTrap(name),
	  _name(name)
{
	setHitPoints(100);
	setEnergyPoints(50);
	setAttackDamage(30);

	std::cout << "DiamondTrap constructor called: " << _name << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other)
	: ClapTrap(other)
	, ScavTrap(other)
	, FragTrap(other)
	, _name(other._name)
{

	std::cout << "DiamondTrap copy constructor called: \n";
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
	std::cout << "DiamondTrap copy assignment called" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other);
		_name = other._name;
	}
	return *this;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap deconstructor called: " << _name << std::endl;
}

void	DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() {
	std::cout << "DiamondTrap name: " << _name
				<< " | ClapTrap name: " << ClapTrap::getName()
				<< std::endl;
}
