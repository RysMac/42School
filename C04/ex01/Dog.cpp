#include "Dog.hpp"
#include "Animal.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog constructor\n";
	brain = new Brain();
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << "Dog cp constructor\n";
	this->brain = new Brain(*other.brain);
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Dog cp. assign.\n";
	if (this != &other)
	{
		Animal::operator=(other);
		*this->brain = *other.brain;
	}
	return *this;
}

Dog::~Dog()
{
	delete brain;
	std::cout << "Dog destructor\n";

}

void Dog::makeSound() const
{
	std::cout << type << " makes hau hau\n";
}
