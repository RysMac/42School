#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include <stdio.h>
#include "SimpleServer.hpp"

namespace HDE
{
	class TestServer : public SimpleServer
	{
	  private:
		void accepter();
		void handler();
		void responder();

	  public:
		TesterServer();
		void launch();
	}
}

#endif // TEST_SERVER_HPP