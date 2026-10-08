#include "ServerManager.hpp"
#include "../net/ListenSocket.hpp"
#include <netinet/in.h>
#include <cstring>
#include <iostream>


ServerManager::ServerManager(const std::vector<int>& ports)
{
	// for n many ports build listening sockets

	const std::string host = "0.0.0.0";

	 std::vector<int>::const_iterator pi;

	for (pi = ports.begin(); pi != ports.end(); ++pi) {
		std::cout << *pi << " ";

		ListenSocket(host, *pi);
	}
	std::cout << std::endl;

	std::cout << "ListenSocket done\n";

}

ServerManager::~ServerManager() {}

void ServerManager::run()
{
sockaddr_in client_address;
	memset(&client_address, 0, sizeof(client_address));

	socklen_t client_address_size = sizeof(client_address);

	int client_socket = accept(
		1,
		(sockaddr*)&client_address,
		&client_address_size
	);

	if (client_socket < 0) { std::cout << "accept failed\n"; }
}

	// char buffer[4096];

	// int bytes_received = recv(
	//     client_socket,
	//     buffer,
	//     sizeof(buffer) - 1,
	//     0
	// );
