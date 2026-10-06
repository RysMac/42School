#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "SimpleServer.hpp"

namespace HDE
{
	class TestServer : public SimpleServer
	{
	  private:
		char buffer[30000] = {0};
		int	 new_socket;

		void accepter();
		void handler();
		void responder();

	  public:
		TestServer();
		void launch();
	};
}

#endif // TEST_SERVER_HPP