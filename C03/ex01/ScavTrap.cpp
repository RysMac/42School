#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

ScavTrap::ScavTrap(const std::string& name)
	: ClapTrap(name) {

		setHitPoints(100);
    	setEnergyPoints(50);
    	setAttackDamage(20);

		std::cout << "ScavTrap constructor called: " << getName() << std::endl;
	}

ScavTrap::ScavTrap(const ScavTrap& other) 
	: ClapTrap(other) 
{
	std::cout << "ScavTrap copy constructor called\n";
};

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
	std::cout << "ScavTrap copy assignment called\n";
    if (this != &other)
        ClapTrap::operator=(other); // assign base part
    return *this;
};

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap destructor called: " << getName() << std::endl;
}

void	ScavTrap::attack(const std::string& target) {
	
	if (getHitPoints() == 0)
	{
		std::cout << "StravTrap " << getName() << " can't attack (no hit points left)." << std::endl;
		return;
	}
	unsigned int curEnerPoints = getEnergyPoints();
	if (curEnerPoints == 0)
	{
		std::cout << "StravTrap " << getName() << " can't attack (no energy points left)." << std::endl;
		return;
	}

	curEnerPoints -= 1;
	setEnergyPoints(curEnerPoints);
	std::cout << "StravTrap " << getName() << " attacks "
			  << target << ", causing " << getAttackDamage()
			  << " points of damage!" << std::endl;
}

void	ScavTrap::guardGate() {
	std::cout << "ScavTrap is in Gate keeper mode" << std::endl;
}
