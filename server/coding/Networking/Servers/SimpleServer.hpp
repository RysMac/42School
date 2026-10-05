#ifndef SIMPLE_SERVER_HPP
#define SIMPLE_SERVER_HPP

#include <stdio.h>

#include "../hdelibc-networking.hpp"

namespace HDE
{
	class SimpleServer
	{
	  private:
		ListeningSocket*	socket;

		virtual void accepter() = 0;
		virtual void handler() = 0;
		virtual void responder() = 0;
	  public:
		SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklog);
		virtual void launch() = 0;
		ListeningSocket* get_socket();
	};
}

#endif // SIMPLE_SERVER_HPP