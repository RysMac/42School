#include "Bureaucrat.h"
#include "Form.h"
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

/* ------------------- Form ------------------- */

static void	testFormConstruction()
{
	title("Form construction");

	try
	{
		Form	taxes("TaxReturn", 50, 25);
		std::cout << taxes << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "unexpected: " << e.what() << std::endl;
	}

	try
	{
		Form	bad("BadSignGrade", 0, 25);
		std::cout << "ERROR: sign grade 0 was accepted" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught (sign grade 0): " << e.what() << std::endl;
	}

	try
	{
		Form	bad("BadExecGrade", 50, 151);
		std::cout << "ERROR: exec grade 151 was accepted" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught (exec grade 151): " << e.what() << std::endl;
	}
}

static void	testSigning()
{
	title("Signing");

	Bureaucrat	boss("Boss", 10);
	Bureaucrat	intern("Intern", 120);

	Form	contract("Contract", 50, 25);
	std::cout << contract << std::endl;

	/* grade 120 is worse than the required 50 -> refused */
	intern.signForm(contract);
	std::cout << contract << std::endl;

	/* grade 10 is better than the required 50 -> accepted */
	boss.signForm(contract);
	std::cout << contract << std::endl;

	/* already signed, signing again still succeeds */
	boss.signForm(contract);
}

static void	testExactGrade()
{
	title("Signing with the exact required grade");

	Bureaucrat	exact("Exact", 50);
	Form		form("Boundary", 50, 25);

	/* equal grades must be enough */
	exact.signForm(form);
	std::cout << form << std::endl;
}

static void	testBeSignedDirectly()
{
	title("beSigned called directly");

	Bureaucrat	weak("Weak", 100);
	Form		form("DirectCall", 40, 20);

	try
	{
		form.beSigned(weak);
		std::cout << "ERROR: beSigned did not throw" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught: " << e.what() << std::endl;
	}
	std::cout << form << std::endl;
}

static void	testCopy()
{
	title("Copy constructor and assignment");

	Bureaucrat	boss("Boss", 5);
	Form		original("Original", 50, 25);

	boss.signForm(original);

	Form	copy(original);
	std::cout << "copy:   " << copy << std::endl;

	Form	other("Other", 80, 60);
	std::cout << "before: " << other << std::endl;
	other = original;
	std::cout << "after:  " << other << std::endl;
	std::cout << "(only the signed flag is copied, the const grades are not)"
			  << std::endl;
}

int	main()
{
	testBureaucratConstruction();
	testBureaucratGrades();
	testFormConstruction();
	testSigning();
	testExactGrade();
	testBeSignedDirectly();
	testCopy();

	std::cout << std::endl;
	return (0);
}
