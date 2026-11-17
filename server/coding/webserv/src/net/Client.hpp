#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include "../http/HttpRequest.hpp"

class Client
{
  public:
	explicit Client(int fd);
	~Client();

	void		set_response(const std::string& out);
	void		add_sent_bytes(size_t sent_bytes);
	const char*	data_to_send() const;
	size_t		bytes_to_send() const;
		
	bool 		get_send_done() const;

	bool		get_request_recv_done() const;
	void		request_save_recv(const char* in, size_t n_bytes);
	
	const HttpRequest&	get_request() const;

  private:
	Client(const Client&);
	Client& operator=(const Client&);

	int			_fd;
	size_t		_sent;   		// how much of _out is already sent
	std::string	_out;    		// full response to send

	HttpRequest	_http_request; 	// parsing requests
};

#endif // CLIENT_HPP
