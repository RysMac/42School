#include "Cat.hpp"
#include "Animal.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat")
{
	 std::cout << "Cat constructor\n";
	 this->brain = new Brain();
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << "Cat cp. constructor\n";
	this->brain = new Brain(*other.brain);
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat cp. assign.\n";
	if ( this != &other)
	{
		Animal::operator=(other);
		*this->brain = *other.brain;
	}
	return *this;
}

Cat::~Cat()
{
	delete brain;
	std::cout << "Cat destructor\n";
}

void Cat::makeSound() const
{
	std::cout << type << " makes miau miau\n";
}
