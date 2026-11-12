#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "../net/ListenSocket.hpp"
#include "../net/Client.hpp"
#include <vector>
#include <poll.h>
#include <map>

struct ServerConfig
{
	std::vector<int>	ports;
	std::string			root;
	std::string			index;
	size_t				client_max_body_size;

};

class ServerManager
{
  public:
	ServerManager(ServerConfig& config);
	~ServerManager();
	void run();

  private:
	ServerManager(const ServerManager&);
	ServerManager& operator=(const ServerManager&);

	ServerConfig				_config;
	std::vector<ListenSocket*>	_sockets;  // vector of pointers bc fd
	std::map<int, Client*>		_clients;  // every client d in _pfds has exactly one entry here
	std::vector<pollfd>			_pfds;
	
	void del_sockets();
	void del_clients();
	void addPfd(int fd);
	void addClient(int fd);
	void delClient(size_t i);


};

#endif // SERVER_MANAGER_HPP
