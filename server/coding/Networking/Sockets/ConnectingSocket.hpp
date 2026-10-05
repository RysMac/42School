#ifndef CONNECTING_SOCKET_HPP
#define CONNECTING_SOCKET_HPP

#include "SimpleSocket.hpp"

namespace HDE
{
	class ConnectingSocket : public SimpleSocket
	{
	  public:
	    // Constructor
		ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);

		// Virtual function from parent
		int connect_to_network(int sock, struct sockaddr_in address);


	  private:

	};
}


#endif // CONNECTING_SOCKET_HPP