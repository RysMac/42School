#include "Harl.hpp"
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
	if (argc != 2)
	{
		std::cout << "[ Probably complaining about insignificant problems ]\n";
		return 0;
	}

	Harl h;
	int idx = h.levelToIndex(argv[1]);

	switch (idx) {
	case 0:
		std::cout << "[ DEBUG ]\n";
		h.complain("DEBUG");
		/* fall through */
	case 1:
		std::cout << "[ INFO ]\n";
		h.complain("INFO");
		/* fall through */
	case 2:
		std::cout << "[ WARNING ]\n";
		h.complain("WARNING");
		/* fall through */
	case 3:
		std::cout << "[ ERROR ]\n";
		h.complain("ERROR");
		break;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]\n";
	}
}
