#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
  public:
	explicit Client(int fd);
	~Client();

  private:
	Client(const Client&);
	Client& operator=(const Client&);

	int			_fd;
	std::string	_in;     // bytes received so far
	std::string	_out;    // full response to send
	size_t		_sent;   // how much of _out is already sent

};

#endif // CLIENT_HPP
