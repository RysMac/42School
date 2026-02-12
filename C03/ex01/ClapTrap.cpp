#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string name) : _name(name),
											 _hitPoints(100),
											 _energyPoints(50),
											 _attackDamage(20)
{
	std::cout << "constructor called: ClapTrap " << name << std::endl;
};

ClapTrap::ClapTrap(const ClapTrap &other) : _name(other._name),
											_hitPoints(other._hitPoints),
											_energyPoints(other._energyPoints),
											_attackDamage(other._attackDamage)
{
	std::cout << "copy constructor called: ClapTrap " << _name << std::endl;
};

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << "copy assignment operator called" << std::endl;
	if (this != &other)
	{
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "deconstructor called: ClapTrap" << _name << std::endl;
};

void ClapTrap::attack(const std::string &target)
{

	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't attack (no hit points left)." << std::endl;
		return;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't attack (no energy points left)." << std::endl;
		return;
	}

	_energyPoints -= 1;
	std::cout << "ClapTrap " << _name << " attacks "
			  << target << ", causing " << _attackDamage
			  << " points of damage!" << std::endl;
};

void ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " takes no damage (already at 0 hit points)." << std::endl;
		return;
	}

	if (amount >= _hitPoints)
	{
		_hitPoints = 0;
		std::cout << "ClapTrap " << _name << " takes " << amount
				  << " points of damage and is now at 0 hit points." << std::endl;
	}
	else
	{
		_hitPoints -= amount;
		std::cout << "ClapTrap " << _name << " takes " << amount
				  << " points of damage and is now at " << _hitPoints << " hit points." << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't repair (no hit points left)." << std::endl;
		return;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't repair (no energy points left)." << std::endl;
		return;
	}

	_energyPoints -= 1;
	_hitPoints += amount;

	std::cout << "ClapTrap " << _name << " repairs itself for " << amount
			  << " hit points, now at " << _hitPoints << " hit points." << std::endl;
}
