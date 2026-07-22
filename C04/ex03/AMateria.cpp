#include "AMateria.hpp"
#include <iostream>

AMateria::AMateria(std::string const &type) : type(type)
{
	std::cout << "AMateria constructor\n";
}

AMateria::AMateria(const AMateria& other)
{
	std::cout << "AMateria copy constructor\n";
	this->type = other.type;
}

AMateria& AMateria::operator=(const AMateria& other)
{
	// don't copy type - intentionally left out
	return *this;
}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor\n";
}

std::string const & AMateria::getType() const
{
	return this->type;
}

void AMateria::use(ICharacter& target)
{
	std::cout << "AMateria : use does nothing here\n";
}
