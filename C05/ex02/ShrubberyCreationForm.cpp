#include "ShrubberyCreationForm.h"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
  : AForm(target + "_shrubbery", 145, 137),
    _target(target)
  {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
  : AForm(other),
	_target(other._target)
  {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}