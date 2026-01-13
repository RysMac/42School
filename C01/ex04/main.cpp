#include <fstream>
#include <iostream>
#include <string>

static std::string replaceAll(const std::string &input,
							  const std::string &s1,
							  const std::string &s2)
{
	std::string out;
	std::string::size_type pos = 0;
	std::string::size_type found;

	while ((found = input.find(s1, pos)) != std::string::npos)
	{
		out.append(input, pos, found - pos);
		out.append(s2);
		pos = found + s1.length();
	}
	out.append(input, pos, std::string::npos);
	return out;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>\n";
		return 1;
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (s1.empty())
	{
		std::cerr << "Error: s1 must not be empty\n";
		return 1;
	}

	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
	if (!in)
	{
		std::cerr << "Error: cannot open input file\n";
		return 1;
	}

	std::string content;
	{
		std::string tmp;
		char ch;
		while (in.get(ch))
			content += ch;
	}

	std::ofstream out((filename + ".replace").c_str(),
					  std::ios::out | std::ios::binary);
	if (!out)
	{
		std::cerr << "Error: cannot open output file\n";
		return 1;
	}

	out << replaceAll(content, s1, s2);
	if (!out)
	{
		std::cerr << "Error: write failed\n";
		return 1;
	}

	return 0;
}
