#include "hdelibc.hpp"



int main()
{
	std::cout << "Starting..." << std::endl;
	//HDE::BindingSocket bind_socket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);
	std::cout << "Banding Socket..." << std::endl;

	HDE::ListeningSocket listening_socket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10);
	std::cout << "Listening Socket..." << std::endl;

	std::cout << "SUCCESS!!\n";

	return 0;
}