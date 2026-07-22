#include "Cat.hpp"
#include "Animal.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat") { std::cout << "Cat constructor\n"; }

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << "Cat cp. constructor\n";
}

Cat& Cat::operator=(const Cat& other)
{
	if ( this != &other)
	{
		Animal::operator=(other);
	}
	std::cout << "Cat cp. assign.\n";
	return *this;
}

Cat::~Cat() { std::cout << "Cat destructor\n"; }

void Cat::makeSound() const
{
	std::cout << _type << " makes miau miau\n";
}
