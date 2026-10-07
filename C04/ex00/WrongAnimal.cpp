#include <string>
#include <iostream>
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : _type("WrongAnimal")
{
	std::cout << "WrongAnimal constructor\n";
}

WrongAnimal::WrongAnimal(std::string type) : _type(type)
{
	std::cout << "WrongAnimal constructor\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	this->_type = other._type;
	std::cout << "WrongAnimal copy constructor called\n";

}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	if (this != &other)
	{
		this->_type = other._type;
	}
	std::cout << "WrongAnimal copy assign. op. called\n";

	return *this;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal destructed\n";
}

const std::string& WrongAnimal::getType() const
{
	return _type;
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal has undefined sound\n";
}
