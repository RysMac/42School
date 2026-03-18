#include "Cure.hpp"
#include "AMateria.hpp"

#include <iostream>

Cure::Cure() : AMateria("cure")
{
	std::cout << "Cure of type: " << getType() << " constructor \n";
}

Cure::Cure(const Cure& other) : AMateria(other)
{
	std::cout << "Cure cp. constructor\n";
}

Cure& Cure::operator=(const Cure& other)
{
	// don't copy type - intentionally left out
	return *this;
}

Cure::~Cure()
{
	std::cout << "Cure destrucotr called\n";
}

Cure* Cure::clone() const
{
	return new Cure(*this);
}

void Cure::use(ICharacter& target)
{
	// empty for now
}
