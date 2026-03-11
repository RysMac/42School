#include "Brain.hpp"
#include "iostream"

Brain::Brain()
{
	for (int i = 0; i < 100; ++i)
	{
		ideas[i] = "empty";
	}
	std::cout << "This is brain constructor\n";
}

Brain::Brain(const Brain& other)
{
	for (int i = 0; i < 100; ++i)
		this->ideas[i] = other.ideas[i];
	std::cout << "This is brain copy constructor\n";
}

Brain& Brain::operator=(const Brain& other)
{
	std::cout << "This is brain copy assign. op.\n";
	if (this != &other)
	{
		for (int i = 0; i < 100; ++i)
			this->ideas[i] = other.ideas[i];
	}

	return *this;
}

Brain::~Brain()
{
	std::cout << "This is brain destructor\n";
}
