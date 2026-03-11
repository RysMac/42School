#include <string>
#include <iostream>
#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
	std::cout << "Animal constructor\n";
}

Animal::Animal(std::string type) : type(type)
{
	std::cout << "Animal constructor\n";
}

Animal::Animal(const Animal& other)
{
	std::cout << "Animal copy constructor called\n";
	this->type = other.type;
}

Animal& Animal::operator=(const Animal& other)
{
	std::cout << "Animal copy assign. op. called\n";
	if (this != &other)
	{
		this->type = other.type;
	}
	return *this;
}

Animal::~Animal()
{
	std::cout << "Animal destructed\n";
}

const std::string& Animal::getType() const
{
	return type;
}

void Animal::makeSound() const
{
	std::cout << "Animal has undefined sound\n";
}
