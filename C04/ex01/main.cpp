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


	const int size = 10;
	Animal* animals[size];

	std::cout << "=== Creating animals ===\n";
	for (int i = 0; i < size / 2; ++i)
		animals[i] = new Dog();

	for (int i = size / 2; i < size; ++i)
		animals[i] = new Cat();

	std::cout << "\n=== Types and sounds ===\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << animals[i]->getType() << ": ";
		animals[i]->makeSound();
	}

	std::cout << "\n=== Deleting animals ===\n";
	for (int i = 0; i < size; ++i)
		delete animals[i];


	return 0;
}
