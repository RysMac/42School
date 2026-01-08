#include <fstream>
#include <string>
#include <iostream>

int	main() {

	std::string file = "abc";
	std::string s1 = "XX";
	std::string	s2 = "co tam slychac";
	std::string	result;

	std::ifstream in((file).c_str());
	if (!in) {
		std::cerr << "Failed to open input file\n";
		return 1;
	}
	std::ofstream out((file + ".replace").c_str());
	if (!out) {
		std::cerr << "Failed to open output file\n";
		return 1;
	}

	std::string line;
	while (std::getline(in, line)) {
		std::cout << line << '\n';
		std::size_t	pos = 0;
		
		while (true) {
			std::size_t found = line.find(s1, pos);

			if (found == std::string::npos) {
				result += line.substr(pos);
				break;
			}
			result += line.substr(pos, found - pos);
			result += s2;
			pos = found + s1.length();
		}
		std::cout << result << std::endl;
		out << result << "\n";
		result = "";
	}


	
	return 0;
}
