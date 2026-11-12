#include "Client.hpp"
#include "../http/HttpRequest.hpp"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>


Client::Client(int fd) : _fd(fd), _sent(0)
{

	std::ifstream file("www/img/logo.png", std::ios::binary);

	if (!file.is_open())
    {
        std::cerr << "Nie można otworzyć pliku\n";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string html = buffer.str();

	std::ostringstream response;
	response << "HTTP/1.1 200 ok\r\n"
			<< "Content-Type: image/png\r\n" // text/html
			<< "Content-Length: " << html.size() << "\r\n"
			<< "Connection: close\r\n"
			<< "\r\n"
			<< html;

	// full message to send
	// this will be removed from here later because it is not Client job to make message to himself
	// but since it is hard coded anyway it can be here for now
	_out = response.str();
}

Client::~Client() { close(_fd); }

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

bool Client::get_send_done() const
{
	return _sent == _out.size();
}

bool Client::get_request_recv_done() const
{
	return _http_request.get_recv_done();
}
void Client::request_save_recv(const char* in, size_t n_bytes)
{
	_http_request.save_recv(in, n_bytes);
}