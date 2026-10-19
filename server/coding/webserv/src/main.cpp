#include "core/ServerManager.hpp"
#include <iostream>
#include <unistd.h>
#include <csignal>

int main()
{
	std::vector<int> ports;

	try 
	{	
		ports.push_back(8080);
		ports.push_back(8081);
		ports.push_back(8082);
		
		ServerManager server(ports);
		// signal(SIGPIPE, SIG_IGN);   // postponed replaces MSG_NOSIGNAL in send remember why
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}
