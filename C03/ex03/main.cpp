#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main()
{
	{
		DiamondTrap cd("quick");
	}

	{
		DiamondTrap d("Dia");
		d.whoAmI();
		d.attack("target");
	}

    DiamondTrap a("A");

    // a.setAttackDamage(3);
    a.attack("TargetDummy");
    // a.status();

	// ScavTrap d("derived");

	ClapTrap* bb = new DiamondTrap("pointer");
	delete(bb);

    a.takeDamage(4);
    // a.status();

    a.beRepaired(5);
    // // a.status();

    // // Drain energy points by attacking
    for (int i = 0; i < 20; i++) {
        a.attack("Dummy");
    }
    // // a.status();

    // // Damage to zero
    a.takeDamage(999);
    // // a.status();

    // // Try actions with 0 HP
    a.beRepaired(10);
    a.attack("Dummy");

    // // Copy tests
    DiamondTrap b = a;
    // b.status();

    DiamondTrap c("C");
    c = b;
    // c.status();
	c.highFivesGuys();

	// different behaviour depending whether attack is virtual or not
	ClapTrap* p = new DiamondTrap("F");
	p->attack("x");
	delete(p);

    return 0;
}
