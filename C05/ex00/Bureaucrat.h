#ifndef BUREAUCRAT_H
#define BUREAUCRAT_H

#include <string>
#include <exception>
#include <ostream>

class Bureaucrat
{
public:
	Bureaucrat();
	Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);
	~Bureaucrat();


	const std::string&	getName() const;
	int					getGrade() const;

	void	increment();
	void	decrement();

	// does these two must be in public or can be also in private - we do not use them outside class
	// does these two must be as nested class? - yes because of spec
	class GradeTooHighException : public std::exception
	{
		public:
			virtual const char* what() const throw(); // what is throw??
	};
	class GradeTooLowException : public std::exception // why public ? because we use exception outside its own?
	{
		public:
			virtual const char* what() const throw();
	};

private:
	const std::string	_name;
	int					_grade;

	void checkGrade(int grade) const;
};

std::ostream& operator << (std::ostream& os, const Bureaucrat& b);

#endif // BUREAUCRAT_H