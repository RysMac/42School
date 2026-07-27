#include "Bureaucrat.h"
#include <iostream>

int main()
{
	std::string name = "bob";
	name = "steve";
	Bureaucrat	br(name, 20);

	Bureaucrat	br2(br);

	std::cout << "Name: " << br2.getName() << "\n";
	std::cout << br2 << "\n";
	try {
		for (int i = 0; i < 200; i++)
			br2.increment();
		std::cout << "no throw (BUG: 200 increments cannot all succeed)\n";
	}
	catch (std::exception& e) {
		std::cout << "loop stopped by: " << e.what() << "\n";
	}
	std::cout << "Grade: " << br2.getGrade() << "\n";

	try {
		Bureaucrat b("bob", 200);
		std::cout << "no throw\n";
	}
	catch (Bureaucrat::GradeTooLowException& e) {
		std::cout << "caught too low\n" << e.what() << "\n";
	}

	std::cout << "Name: " << br2.getName() << "\n";

	try {
		Bureaucrat b("bob", 200);
		std::cout << "no throw\n";
	}
	catch (std::exception& e) {
		std::cout << "caught too low\n" << e.what() << "\n";
		// e.what();
	}

	std::cout << "\n--- increment / decrement: normal cases ---\n";

	try {
		Bureaucrat	worker("worker", 3);

		std::cout << "start:  " << worker << "\n";
		worker.increment();
		std::cout << "inc:    " << worker << "\n";
		worker.decrement();
		worker.decrement();
		std::cout << "dec x2: " << worker << "\n";
	}
	catch (std::exception& e) {
		std::cout << "unexpected throw: " << e.what() << "\n";
	}

	std::cout << "\n--- increment at the top (grade 1) ---\n";

	Bureaucrat	best("best", 1);

	std::cout << "before: " << best << "\n";
	try {
		best.increment();
		std::cout << "no throw (BUG: grade 0 must be impossible)\n";
	}
	catch (std::exception& e) {
		std::cout << "caught: " << e.what() << "\n";
	}
	std::cout << "after:  " << best << "\n";

	std::cout << "\n--- decrement at the bottom (grade 150) ---\n";

	Bureaucrat	worst("worst", 150);

	std::cout << "before: " << worst << "\n";
	try {
		worst.decrement();
		std::cout << "no throw (BUG: grade 151 must be impossible)\n";
	}
	catch (std::exception& e) {
		std::cout << "caught: " << e.what() << "\n";
	}
	std::cout << "after:  " << worst << "\n";

	return 0;
}