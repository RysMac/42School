#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
  public:
	explicit Client(int fd);
	~Client();

	void		save_recv(const char* in, size_t n_bytes);
	void		add_sent_bytes(size_t sent_bytes);
	const char*	data_to_send() const;
	size_t		bytes_to_send() const;
	
	bool		get_recv_done() const;
	bool 		get_send_done() const;

  private:
	Client(const Client&);
	Client& operator=(const Client&);

	int			_fd;
	size_t		_sent;   // how much of _out is already sent
	bool		_recv_done;  // have we received the whole data?
	std::string	_in;     // bytes received so far
	std::string	_out;    // full response to send
};

#endif // CLIENT_HPP
