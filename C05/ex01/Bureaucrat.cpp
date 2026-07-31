#include <string>
#include "Bureaucrat.h"
#include "Form.h"
#include <iostream>

Bureaucrat::Bureaucrat() : _name(""), _grade(150) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
	: _name(name),
	  _grade(grade)
	{
		checkGrade(grade);
	}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
	: _name(other._name),
	  _grade(other._grade)
	{}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this!=&other)
		_grade = other._grade;
	
	return (*this); 
}

Bureaucrat::~Bureaucrat() {}

const std::string& Bureaucrat::getName() const
{
	return _name;
}

int Bureaucrat::getGrade() const
{
	return _grade;
}

void Bureaucrat::increment()
{
	checkGrade(_grade - 1);
	_grade--;
}

void Bureaucrat::decrement()
{
	checkGrade(_grade + 1);
	_grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Bureaucrat grade too high (highest is 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Bureaucrat grade too low (lowest is 150)";
}

void Bureaucrat::checkGrade(int grade) const 
{
	if (grade < 1) throw GradeTooHighException();
	if (grade > 150) throw GradeTooLowException();
}

void Bureaucrat::signForm(Form& f)
{
	try
	{
		f.beSigned(*this);
		std::cout << _name << " signed " << f.getName() << std::endl;
	}	
	catch(const std::exception& e)
	{
		std::cout << _name << " couldn't sign " << f.getName()
				  << " because " << e.what() << "." << std::endl;
	}
}

std::ostream& operator << (std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}
