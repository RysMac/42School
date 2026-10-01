#ifndef AForm_H
#define AForm_H

#include <string>
#include <iostream>
#include <ostream>
#include <exception>
#include "Bureaucrat.h"

class AForm
{
  public:
	AForm();
	AForm(const std::string& name,
		 int grade_sign,
		 int grade_exec);
	AForm(const AForm& other);
	AForm& operator=(const AForm& f);
	virtual ~AForm();

	const std::string& 	getName() const;
	bool 				getSigned() const;
	int		 			getGradeToSign() const;
	int 				getGradeToExec() const;

	class GradeTooHighException : public std::exception
	{
		public:
			virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
		public:
			virtual const char* what() const throw();
	};

	void	beSigned(const Bureaucrat& b);

	virtual void execute(const Bureaucrat& executor) const = 0; 
  
  private:
	const std::string	_name;
	bool 				_signed;
	const int			_grade_sign;
	const int			_grade_exec;

	void	checkGrade(int grade) const;

};

std::ostream& operator << (std::ostream& os, const AForm& f);

#endif // AForm_H