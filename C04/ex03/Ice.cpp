#include "Ice.hpp"
#include "AMateria.hpp"

#include <iostream>

Ice::Ice() : AMateria("ice")
{
	std::cout << "Ice of type: " << getType() << " constructor \n";
}

Ice::Ice(const Ice& other) : AMateria(other)
{
	std::cout << "Ice cp. constructor\n";
}

Ice& Ice::operator=(const Ice& other)
{
	// don't copy type - intentionally left out
	return *this;
}

Ice::~Ice()
{
	std::cout << "Ice destrucotr called\n";
}

Ice* Ice::clone() const
{
	return new Ice(*this);
}

void Ice::use(ICharacter& target)
{
	// empty for now
}
