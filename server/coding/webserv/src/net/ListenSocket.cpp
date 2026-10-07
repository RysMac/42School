#include "ListenSocket.hpp"
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

ListenSocket::ListenSocket(const std::string& host, int port)
	: _fd(-1), _port(port)
{

	(void)host;

	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0) { fail("socket"); }

	int opt = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) { fail("setsockopt"); }

	if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0) { fail("fcntl"); }

	sockaddr_in server_address;
	std::memset(&server_address, 0, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(_port);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); // host ??

	if (bind(_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0) { fail("bind"); }

	if (listen(_fd , SOMAXCONN) < 0) { fail("listen"); }
}

ListenSocket::~ListenSocket() { if (_fd >= 0) { close(_fd); } }

int ListenSocket::getFd() const { return _fd; }

int ListenSocket::getPort() const { return _port; }

// Build the message first (close() may overwrite errno), release the fd, throw.
void ListenSocket::fail(const std::string& step)
{
	std::ostringstream oss;
	oss << step << "(" << _port << "): " << std::strerror(errno);

	if (_fd >= 0)
	{
		close(_fd);
		_fd = -1;
	}
	throw SocketError(oss.str());
}

ListenSocket::SocketError::SocketError(const std::string& msg)
	: std::runtime_error(msg)
{}
