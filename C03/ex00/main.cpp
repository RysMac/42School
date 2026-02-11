#include "ClapTrap.hpp"

int main()
{
    ClapTrap a("A");
    // a.status();

    // a.setAttackDamage(3);
    a.attack("TargetDummy");
    // a.status();

    a.takeDamage(4);
    // a.status();

    a.beRepaired(5);
    // a.status();

    // Drain energy points by attacking
    for (int i = 0; i < 20; i++) {
        a.attack("Dummy");
    }
    // a.status();

    // Damage to zero
    a.takeDamage(999);
    // a.status();

    // Try actions with 0 HP
    a.beRepaired(10);
    a.attack("Dummy");

    // Copy tests
    ClapTrap b = a;
    // b.status();

    ClapTrap c("C");
    c = b;
    // c.status();

    return 0;
}
