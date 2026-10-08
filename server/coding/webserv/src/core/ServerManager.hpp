#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <vector>

class ServerManager
{
  public:
	ServerManager(const std::vector<int>& ports);
	~ServerManager();

  private:
	void run();
};

#endif // SERVER_MANAGER_HPP
