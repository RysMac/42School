#include "FragTrap.hpp"

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {

	setHitPoints(100);
   	setEnergyPoints(100);
   	setAttackDamage(30);

	std::cout << "FragTrap constructor called: " << getName() << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
	std::cout << "FragTrap copy construcotr called " << std::endl;	
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
	std::cout << "FragTrap copy assignment called\n";
    if (this != &other)
        ClapTrap::operator=(other); // assign base part
    return *this;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap deconstructor called: " << getName() << std::endl;
}

void	FragTrap::attack(const std::string& target) {
	
	if (getHitPoints() == 0)
	{
		std::cout << "FragTrap " << getName() << " can't attack (no hit points left)." << std::endl;
		return;
	}
	unsigned int curEnerPoints = getEnergyPoints();
	if (curEnerPoints == 0)
	{
		std::cout << "FragTrap " << getName() << " can't attack (no energy points left)." << std::endl;
		return;
	}

	curEnerPoints -= 1;
	setEnergyPoints(curEnerPoints);
	std::cout << "FragTrap " << getName() << " attacks "
			  << target << ", causing " << getAttackDamage()
			  << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << getName() << " requests a positive high five!" << std::endl;
}