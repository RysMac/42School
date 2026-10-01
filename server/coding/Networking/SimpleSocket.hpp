#ifndef SIMPLE_SOCKET_HPP
#define SIMPLE_SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

namespace HDE
{
	class SimpleSocket
	{
	  public:
		// Constructor
		SimpleSocket(int domain, int serveice, int protocol, int port, u_long interface);
		// Virtual function to connect to a network
		virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
		// Testing if a socket/connection succeed
		void test_connection(int);

		//Getter functions
		struct sockaddr_in get_address();
		int get_sock();
		int get_connection();
		//Setter functions
		void set_connection(int connection_fd);

	  private:
		struct sockaddr_in address;
		int	sock;
		int connection;

	};
}


#endif /* SIMPLE_SOCKET_HPP */