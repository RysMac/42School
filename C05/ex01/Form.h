#ifndef FORM_H
#define FORM_H

#include <string>
#include <iostream>
#include <ostream>
#include <exception>
#include "Bureaucrat.h"

class Form
{
  public:
	Form();
	Form(const std::string& name,
		 int grade_sign,
		 int grade_exec);
	Form(const Form& other);
	Form& operator=(const Form& f);
	~Form();

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
  
  private:
	const std::string	_name;
	bool 				_signed;
	const int			_grade_sign;
	const int			_grade_exec;

	void	checkGrade(int grade) const;

};

std::ostream& operator << (std::ostream& os, const Form& f);

#endif // FORM_H