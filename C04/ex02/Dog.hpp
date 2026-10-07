#ifndef DOG_HPP
#define DOG_HPP

#include "Brain.hpp"
#include "Animal.hpp"
#include <string>

class Dog : public Animal
{
private:
	Brain*	brain;
public:
	Dog();
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	~Dog();
	virtual void makeSound() const;
};

#endif
