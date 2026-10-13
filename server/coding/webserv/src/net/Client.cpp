#include "Client.hpp"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sstream>


Client::Client(int fd) : _fd(fd), _sent(0), _recv_done(false)
{

	const char* body =
		"<html>"
		"<body>"
		"<h1>Hello!</h1>"
		"</body>"
		"</html>";
	std::ostringstream response;
	response << "HTTP/1.1 200 OK\r\n"
			<< "Content-Type: text/html\r\n"
			<< "Content-Length: " << std::strlen(body) << "\r\n"
			<< "Connection: close\r\n"
			<< "\r\n"
			<< body;

	// full message to send
	// this will be removed from here latet because it is not Client job to make message to himself
	// but since it is hard coded anyway it can be here for now
	_out = response.str();
}

Client::~Client() { close(_fd); }

void Client::save_recv(const char* in, size_t n_bytes)
{
	_in.append(in, n_bytes);
	if (_in.find("\r\n\r\n") != std::string::npos)
		_recv_done = true;
}

void Client::add_sent_bytes(size_t sent_bytes)
{
	_sent += sent_bytes;
}

const char* Client::data_to_send() const
{
	return _out.c_str() + _sent;
}

size_t Client::bytes_to_send() const
{
	return _out.size() - _sent;
}

bool Client::get_recv_done() const
{
	return _recv_done;
}

bool Client::get_send_done() const
{
	return _sent == _out.size();
}
