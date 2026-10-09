#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "../net/ListenSocket.hpp"
#include <vector>

class ServerManager
{
  public:
	ServerManager(const std::vector<int>& ports);
	~ServerManager();

  private:
	ServerManager(const ServerManager&);
	ServerManager& operator=(const ServerManager&);

	std::vector<ListenSocket*>	_sockets;  // vector of poinrterss

	void del_sockets();
	
};

#endif // SERVER_MANAGER_HPP
