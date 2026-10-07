#include <string>
#include <iostream>
#include "Animal.hpp"

Animal::Animal() : _type("Animal")
{
	std::cout << "Animal constructor\n";
}

Animal::Animal(std::string type) : _type(type)
{
	std::cout << "Animal constructor\n";
}

Animal::Animal(const Animal& other)
{
	this->_type = other._type;
	std::cout << "Animal copy constructor called\n";

}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
	{
		this->_type = other._type;
	}
	std::cout << "Animal copy assign. op. called\n";

	return *this;
}

Animal::~Animal()
{
	std::cout << "Animal destructed\n";
}

const std::string& Animal::getType() const
{
	return _type;
}

void Animal::makeSound() const
{
	std::cout << "Animal has undefined sound\n";
}
