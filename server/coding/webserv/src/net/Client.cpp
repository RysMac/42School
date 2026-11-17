#include "Client.hpp"
#include "../http/HttpRequest.hpp"
#include <cstring>
#include <unistd.h>
#include <iostream>


Client::Client(int fd) : _fd(fd), _sent(0) {}

Client::~Client() { close(_fd); }

void Client::set_response(const std::string& out)
{
	_out = out;
	_sent = 0;
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

const HttpRequest& Client::get_request() const
{
	return _http_request;
}