#include "WrongCat.hpp"
#include "WrongAnimal.hpp"
#include <iostream>

WrongCat::WrongCat() : WrongAnimal("WrongCat") { std::cout << "WrongCat constructor\n"; }

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	std::cout << "WrongCat cp. constructor\n";
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	if ( this != &other)
	{
		WrongAnimal::operator=(other);
	}
	std::cout << "WrongCat cp. assign.\n";
	return *this;
}

WrongCat::~WrongCat() { std::cout << "WrongCat destructor\n"; }

void WrongCat::makeSound() const
{
	std::cout << _type << " makes miau miau\n";
}
