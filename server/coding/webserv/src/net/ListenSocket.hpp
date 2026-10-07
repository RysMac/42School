#ifndef LISTEN_SOCKET_HPP
#define LISTEN_SOCKET_HPP

#include <string>
#include <stdexcept>


class ListenSocket
{
  public:
	ListenSocket(const std::string& host, int port);
	~ListenSocket();

	int	getFd() const;
	int	getPort() const;

	class SocketError : public std::runtime_error
	{
	  public:
		SocketError(const std::string& msg);
	};

  private:
	ListenSocket(const ListenSocket&);            // copying disabled
	ListenSocket& operator=(const ListenSocket&); // (declared, never defined)

	void	fail(const std::string& step);

	int 	_fd;
	int 	_port;

};


#endif // LISTEN_SOCKET_HPP
