#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string& name) : _name(name),
											 _hitPoints(10),
											 _energyPoints(10),
											 _attackDamage(0)
{
	std::cout << "ClapTrap constructor called :  " << name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) : _name(other._name),
											_hitPoints(other._hitPoints),
											_energyPoints(other._energyPoints),
											_attackDamage(other._attackDamage)
{
	std::cout << "ClapTrap copy constructor called: " << _name << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
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
	std::cout << "ClapTrap destructor called: " << _name << std::endl;
}

const std::string& ClapTrap::getName() const { return _name; }
unsigned int ClapTrap::getHitPoints() const { return _hitPoints; }
unsigned int ClapTrap::getEnergyPoints() const { return _energyPoints; }
unsigned int ClapTrap::getAttackDamage() const { return _attackDamage; }

void ClapTrap::setName(const std::string& name) { _name = name; }
void ClapTrap::setHitPoints(unsigned int amount) { _hitPoints = amount; }
void ClapTrap::setEnergyPoints(unsigned int amount) { _energyPoints = amount; }
void ClapTrap::setAttackDamage(unsigned int amount) { _attackDamage = amount; }

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
