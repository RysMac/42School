#include "Form.h"


Form::Form() : _name(""), _signed(false), _grade_sign(1), _grade_exec(150) {}

Form::Form(const std::string& name, int grade_sign, int grade_exec)
  : _name(name),
    _signed(false),
	_grade_sign(grade_sign),
	_grade_exec(grade_exec)
  {
	checkGrade(grade_sign);
	checkGrade(grade_exec);
  }

Form::Form(const Form& other)
  : _name(other._name),
  	_signed(other._signed),
  	_grade_sign(other._grade_sign),
	_grade_exec(other._grade_exec)
  {}

Form& Form::operator=(const Form& other)
{
	if (this!=&other)
		_signed=other._signed;

	return (*this);
}

Form::~Form() {}

const std::string& Form::getName() const
{
	return _name;
}

bool Form::getSigned() const
{
	return _signed;
}

int Form::getGradeToSign() const
{
	return _grade_sign;
}

int Form::getGradeToExec() const
{
	return _grade_exec;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "the grade is too high (1 is the highest)";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "the grade is too low";
}

void Form::checkGrade(int grade) const
{
	if (grade < 1) throw GradeTooHighException();
	if (grade > 150) throw GradeTooLowException();
}

void Form::beSigned(const Bureaucrat& b)
{
	if (b.getGrade() > _grade_sign)
		throw GradeTooLowException(); 
		
	_signed = true;
}

std::ostream& operator << (std::ostream& os, const Form& f)
{
	os << "Form " << f.getName()
	   << ", signed: " << (f.getSigned() ? "yes" : "no")
	   << ", grade to sign: " << f.getGradeToSign()
	   << ", grade to execute: " << f.getGradeToExec() << ".";

	return os;
}