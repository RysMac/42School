#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria
{
public:
	Cure();
	Cure(const Cure& other);
	Cure& operator=(const Cure& other);
	~Cure();

	virtual Cure*	clone() const; // pure virtual function
    virtual void	use(ICharacter& target);
};

#endif
