#ifndef ShrubberyCreationForm_H
#define ShrubberyCreationForm_H

#include "AForm.h"

class ShrubberyCreationForm : public AForm
{
  public:
	// ShrubberyCreationForm(); // Default one should it be here? -> private?
	ShrubberyCreationForm(const std::string& target);
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
	~ShrubberyCreationForm();

  private:
    const std::string _target;


};



#endif // ShrubberyCreationForm_H