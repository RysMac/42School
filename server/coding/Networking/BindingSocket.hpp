#ifndef BINDING_SOCKET_HPP
#define BINDING_SOCKET_HPP

#include <stdio.h>
#include "SimpleSocket.hpp"

namespace HDE
{
	class BindingSocket : public SimpleSocket
	{
	  public:
	    // Constructor
		BindingSocket(int domain, int service, int protocol, int port, u_long interface);

		// Virtual function from parent
		int connect_to_network(int sock, struct sockaddr_in address);


	  private:

	};
}


#endif // BINDING_SOCKET_HPP