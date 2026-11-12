#include "core/ServerManager.hpp"
#include <iostream>
#include <unistd.h>
#include <csignal>


// STAB
ServerConfig makeTestConfig()
{

	ServerConfig	sconf;

	sconf.ports.push_back(8080);
	sconf.ports.push_back(8081);
	sconf.ports.push_back(8082);

	sconf.root					= "www";
	sconf.index 				= "index.html";
	sconf.client_max_body_size	= 1024 * 1024;

	return sconf;
}



int main()
{

	signal(SIGPIPE, SIG_IGN);   // replaces MSG_NOSIGNAL => SIGPIPE cant kill server

	try 
	{	
		ServerConfig	configuration;
		configuration = makeTestConfig();
		ServerManager server(configuration);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}
