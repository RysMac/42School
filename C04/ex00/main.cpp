#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
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
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		std::cout << meta->getType() << " " << std::endl;
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound();
		j->makeSound();
		meta->makeSound();
		delete meta;
		delete j;
		delete i;
	}

	std::cout << "---- WRONG ANIMALS ----\n";

	const WrongAnimal* wa = new WrongAnimal();
	const WrongAnimal* wc = new WrongCat();

	std::cout << wa->getType() << std::endl;
	std::cout << wc->getType() << std::endl;

	wa->makeSound();    // WrongAnimal sound
	wc->makeSound();    // also WrongAnimal sound

	delete wa;
	delete wc;
	return 0;
}
