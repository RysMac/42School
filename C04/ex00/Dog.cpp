#include "Dog.hpp"
#include "Animal.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") { std::cout << "Dog constructor\n"; }

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << "Dog cp constructor\n";
}

Dog& Dog::operator=(const Dog& other)
{
	if (this != &other)
	{
		Animal::operator=(other);
	}
	std::cout << "Dog cp. assign.\n";
	return *this;
}

Dog::~Dog() { std::cout << "Dog deconstructor\n"; }

void Dog::makeSound() const
{
	std::cout << _type << " makes hau hau\n";
}
