
#include <iostream>
#include "Zombie.hpp"


int	main() {


	randomChump( "Foo1" );

	Zombie* z = newZombie("Foo2");
	z->announce();
	delete z;

	return 0;
}