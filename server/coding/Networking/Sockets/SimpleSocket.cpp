#include "SimpleSocket.hpp"
#include <cstdlib>

HDE::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
{
	// define address structure
	address.sin_family		= domain;
	address.sin_port		= htons(port);
	address.sin_addr.s_addr = htonl(interface);
	// establish socket
	sock = socket(domain, service, protocol);
	test_connection(sock);
}

// Test connection virtual function
void HDE::SimpleSocket::test_connection(int item_to_test)
{
	if (item_to_test < 0)
	{
		perror("Failed to connect...");
		exit(EXIT_FAILURE);
	}
}

// Getter functions
struct sockaddr_in HDE::SimpleSocket::get_address()
{
	return address;
}

int HDE::SimpleSocket::get_sock()
{
	return sock;
}

int HDE::SimpleSocket::get_connection()
{
	return connection;
}

// Setters function
void HDE::SimpleSocket::set_connection(int connection_fd)
{
	connection = connection_fd;
}