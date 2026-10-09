#include "ServerManager.hpp"
#include "../net/ListenSocket.hpp"
#include <iostream>

ServerManager::ServerManager(const std::vector<int>& ports)
{
	const std::string host = "0.0.0.0";

	try
	{
		_sockets.reserve(ports.size());
		std::vector<int>::const_iterator pi;
		for (pi = ports.begin(); pi != ports.end(); ++pi) {

			ListenSocket *s = new ListenSocket(host, *pi);
			_sockets.push_back(s);
		}
		std::cout << "ListenSocket success\n";
	}
	catch(...)
	{
		del_sockets();
		throw;
	}
}

ServerManager::~ServerManager()
{
	del_sockets();
}

void ServerManager::del_sockets()
{
	//every _socket member must be deleted
	std::vector<ListenSocket*>::const_iterator si;
	for (si = _sockets.begin(); si != _sockets.end(); ++si)
	{
		delete (*si);
	}
	_sockets.clear();
}