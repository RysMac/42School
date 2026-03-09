#include "Animal.hpp"
#include "Dog.hpp"
#include <iostream>


int main()
{

	{
		Animal a1;
		Animal a2 = a1;

		a2 = a1;
		a2.makeSound();
	}


	{
		Dog d;
		d.makeSound();

		Dog d1 = d;
		Dog d2;
		d2 = d1;
	}

	{
		Animal *a = new Dog();
		a->makeSound();
		delete a;
	}
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	std::cout << meta->getType() << " " << std::endl;
	std::cout << j->getType() << " " << std::endl;
	delete meta;
	delete j;

	return 0;
}
