#include "AForm.h"


AForm::AForm() : _name(""), _signed(false), _grade_sign(1), _grade_exec(150) {}

AForm::AForm(const std::string& name, int grade_sign, int grade_exec)
  : _name(name),
    _signed(false),
	_grade_sign(grade_sign),
	_grade_exec(grade_exec)
  {
	checkGrade(grade_sign);
	checkGrade(grade_exec);
  }

AForm::AForm(const AForm& other)
  : _name(other._name),
  	_signed(other._signed),
  	_grade_sign(other._grade_sign),
	_grade_exec(other._grade_exec)
  {}

AForm& AForm::operator=(const AForm& other)
{
	if (this!=&other)
		_signed=other._signed;

	return (*this);
}

AForm::~AForm() {}

const std::string& AForm::getName() const
{
	return _name;
}

bool AForm::getSigned() const
{
	return _signed;
}

int AForm::getGradeToSign() const
{
	return _grade_sign;
}

int AForm::getGradeToExec() const
{
	return _grade_exec;
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "the grade is too high (1 is the highest)";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "the grade is too low";
}

void AForm::checkGrade(int grade) const
{
	if (grade < 1) throw GradeTooHighException();
	if (grade > 150) throw GradeTooLowException();
}

void AForm::beSigned(const Bureaucrat& b)
{
	if (b.getGrade() > _grade_sign)
		throw GradeTooLowException(); 
		
	_signed = true;
}

std::ostream& operator << (std::ostream& os, const AForm& f)
{
	os << "AForm " << f.getName()
	   << ", signed: " << (f.getSigned() ? "yes" : "no")
	   << ", grade to sign: " << f.getGradeToSign()
	   << ", grade to execute: " << f.getGradeToExec() << ".";

	return os;
}