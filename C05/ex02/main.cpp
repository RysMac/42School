#include "Bureaucrat.h"
#include "AForm.h"
#include <iostream>

static void	title(const std::string& s)
{
	std::cout << "\n===== " << s << " =====" << std::endl;
}

/* ---------------- Bureaucrat ---------------- */

static void	testBureaucratConstruction()
{
	title("Bureaucrat construction");

	try
	{
		Bureaucrat	boss("Boss", 1);
		std::cout << boss << std::endl;

		Bureaucrat	intern("Intern", 150);
		std::cout << intern << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "unexpected: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	tooHigh("TooHigh", 0);
		std::cout << "ERROR: grade 0 was accepted" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught (grade 0): " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	tooLow("TooLow", 151);
		std::cout << "ERROR: grade 151 was accepted" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught (grade 151): " << e.what() << std::endl;
	}
}

static void	testBureaucratGrades()
{
	title("Bureaucrat increment / decrement");

	Bureaucrat	clerk("Clerk", 3);

	std::cout << clerk << std::endl;
	clerk.increment();
	std::cout << "after increment: " << clerk << std::endl;
	clerk.decrement();
	std::cout << "after decrement: " << clerk << std::endl;

	Bureaucrat	top("Top", 1);
	try
	{
		top.increment();
		std::cout << "ERROR: incremented past grade 1" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught (increment at 1): " << e.what() << std::endl;
	}
	std::cout << "unchanged: " << top << std::endl;

	Bureaucrat	bottom("Bottom", 150);
	try
	{
		bottom.decrement();
		std::cout << "ERROR: decremented past grade 150" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught (decrement at 150): " << e.what() << std::endl;
	}
	std::cout << "unchanged: " << bottom << std::endl;
}


int	main()
{
	testBureaucratConstruction();
	testBureaucratGrades();

	std::cout << std::endl;
	return (0);
}
