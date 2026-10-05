#include "ConnectingSocket.hpp"

// Constructor
HDE::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long interface)
		 : SimpleSocket(domain, service, protocol, port, interface)
{
	// This is bind or connect to establish connection
	set_connection(connect_to_network(get_sock(), get_address())); 
	test_connection(get_connection());
}

// Implementation of connect_to_network pure virtual function
int HDE::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	return connect(sock, (sockaddr*)&address, sizeof(address));
}