#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "../net/ListenSocket.hpp"
#include <vector>
#include <poll.h>

class ServerManager
{
  public:
	ServerManager(const std::vector<int>& ports);
	~ServerManager();
	void run();

  private:
	ServerManager(const ServerManager&);
	ServerManager& operator=(const ServerManager&);

	std::vector<ListenSocket*>	_sockets;  // vector of poinrterss
	std::vector<pollfd>			_pfds;

	void del_sockets();
	void addPfd(int fd);
	
	
};

#endif // SERVER_MANAGER_HPP
