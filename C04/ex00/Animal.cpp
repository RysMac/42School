#include <string>
#include <iostream>
#include "Animal.hpp"

Animal::Animal() : _type("Animal")
{
	std::cout << _type << " constructor\n";
}

Animal::Animal(std::string type) : _type(type)
{
	std::cout << _type << " constructor\n";
}

Animal::Animal(const Animal& other)
{
	this->_type = other._type;
	std::cout << _type << " copy constructor called\n";

}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
	{
		this->_type = other._type;
	}
	std::cout << _type << " copy assign. op. called\n";

	return *this;
}

Animal::~Animal()
{
	std::cout << _type << " destructed\n";
}

const std::string& Animal::getType() const
{
	return _type;
}

void Animal::makeSound()
{
	std::cout << _type << " has undefined sound\n";
}
