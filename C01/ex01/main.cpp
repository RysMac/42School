#include <iostream>
#include "Zombie.hpp"

int	main() {

	int n = 10;
	Zombie* hord = zombieHorde(n, "foo");
	for (int i = 0; i < n; i++) {
		hord[i].announce();
	}

	delete[] hord;

	return 0;
}