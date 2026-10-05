#ifndef LISTENING_SOCKET_HPP
#define LISTENING_SOCKET_HPP

#include <iostream>
#include "BindingSocket.hpp"

namespace HDE
{
	class ListeningSocket : public BindingSocket
	{
	  public:
		ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklog);
		void start_listening();
	  private:
		int backlog;
		int listening;
	};
}


#endif // LISTENING_SOCKET_HPP