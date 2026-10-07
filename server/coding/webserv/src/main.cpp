#include "net/ListenSocket.hpp"
#include <iostream>
#include <unistd.h>

int main()
{
	try
	{
		ListenSocket ls0("0.0.0.0", 8081);
		ListenSocket ls1("0.0.0.0", 8080);
		ListenSocket ls2("0.0.0.0", 8080);
		// ListenSocket dup("0.0.0.0", 8080);   // test: bind(8080): Address already in use

		std::cout << "listening on " << ls0.getPort() << " and " << ls1.getPort() << std::endl;
		pause();                                // keep alive, check with: ss -ltn | grep 808
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
