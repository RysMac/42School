#include <fstream>
#include <string>
#include <iostream>

int	main() {

	std::string str = "abc";
	std::ofstream out((str + ".replace").c_str());
	if (!out) {
		std::cerr << "Failed to open output file\n";
		return 1;
	}

	out << "abc XX abc YY abc \n";
	out.close();

	std::ifstream in((str + ".replace").c_str());
	if (!in) {
		std::cerr << "Failed to open input file\n";
		return 1;
	}

	std::string line;
	if (!std::getline(in, line)) {
		std::cout << " getline error " << "\n";
		return 1;
	}
	std::cout << line << '\n';

	std::size_t found = line.find("YY", 0);

	std::cout << found << std::endl;

	// while (std::getline(in, line)) std::cout << line << '\n';

	return 0;
}
