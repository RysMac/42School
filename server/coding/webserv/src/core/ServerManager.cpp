#include "ServerManager.hpp"
#include "../net/ListenSocket.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

#define BUFFER_SIZE 1024

ServerManager::ServerManager(const std::vector<int>& ports)
{
	const std::string host = "0.0.0.0";

	try
	{
		_sockets.reserve(ports.size());
		std::vector<int>::const_iterator pi;
		for (pi = ports.begin(); pi != ports.end(); ++pi) {

			ListenSocket *s = new ListenSocket(host, *pi);
			_sockets.push_back(s);
		}
		std::cout << "ListenSocket success\n";

		_pfds.reserve(_sockets.size());
		for (size_t i = 0; i < _sockets.size(); ++i)
			addPfd(_sockets[i]->getFd());
	}
	catch(...)
	{
		del_sockets();
		throw;
	}
}

ServerManager::~ServerManager()
{
	del_sockets();
}

void ServerManager::del_sockets()
{
	//every _socket member must be deleted
	std::vector<ListenSocket*>::const_iterator si;
	for (si = _sockets.begin(); si != _sockets.end(); ++si)
	{
		delete (*si);
	}
	_sockets.clear();
}

void ServerManager::run()
{

	char buffer[BUFFER_SIZE];

	while (true)
	{
		int poll_count = poll(&_pfds[0], _pfds.size(), -1); // -1 must be changed acc to spec ?

		if (poll_count < 0) { throw std::runtime_error("poll failed"); }
		size_t	current_size = _pfds.size();
		for (size_t i = 0; i < current_size; ++i)
		{
			if (_pfds[i].revents == 0) continue;

			if (i >= _sockets.size() &&_pfds[i].revents & (POLLERR | POLLHUP)) // this cannot happen to listen sockets right? - POLLERR is possible but rare 
			{
				std::cout << "Error from client socket. FD: " << _pfds[i].fd << "\n";
				close(_pfds[i].fd);
				if (i != _pfds.size() - 1) _pfds[i] = _pfds.back();
				_pfds.pop_back();
				--current_size;
				--i; // go back one i to inspect already placed one next time
			}
			// A. Obsluga gniazda serwera (Nowy Klient)
			else if ( i < _sockets.size() ) // this must be true only for server_fd
			{
				if (_pfds[i].revents & POLLIN)
				{			
					int client_fd = accept(_sockets[i]->getFd(), NULL, NULL);
					if (client_fd >= 0) 
					{
						std::cout << "New client connected! FD: " << client_fd << "\n";
						if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
						{
							close(client_fd);
							continue; // == go to for loop increase ++i and go on
						}
						/*  increses vector - should I increase current_size?
							- no after this we should also continue the for loop and the next poll will check this slot
						*/  
						addPfd(client_fd); 
						continue;
					}
				}
			}
			else // B. Obsługa istniejących klientów (Dane wejściowe lub Rozłączenie)
			{
				if (_pfds[i].revents & POLLIN)
				{
					std::memset(buffer, 0, BUFFER_SIZE);
					ssize_t bytes_read = recv(_pfds[i].fd, buffer, BUFFER_SIZE - 1, 0);

					if (bytes_read <= 0) // this means that recv failed
					{
						std::cout << "Client disconnected. FD: " << _pfds[i].fd << "\n";
						close(_pfds[i].fd);
						
						if (i != _pfds.size() - 1)
							_pfds[i] = _pfds.back(); // replace clsed client space by the last one
						_pfds.pop_back(); // delete the last element
						--current_size;
                        --i;
						continue; // not needed but clarify waht is next
					}
					else
					{
						buffer[bytes_read] = '\0';
						std::cout << "Received from FD: " << _pfds[i].fd << ": " << buffer;
						_pfds[i].events = POLLOUT;
					}
				}
				else if (_pfds[i].revents & POLLOUT)
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

					std::string out = response.str();
					// TODO: replace MSG_NOSIGNAL by signal(SIGPIPE, SIG_IGN) later
					if (send(_pfds[i].fd, out.c_str(), out.size(), MSG_NOSIGNAL) <= 0)
					{
						// close -> replace -> move on with current i again
						close(_pfds[i].fd);
						if (i != _pfds.size() - 1) _pfds[i] = _pfds.back();
						_pfds.pop_back();
						--current_size;
						--i;
						continue;
					}
					else
					{
						// TODO partial send: if send < out.size() keep the rest, don't close
						// close -> replace -> move on with current i again 
						// TODO: make a member delClient() later, there are 4 time we are using the same strucutre already
						close(_pfds[i].fd);
						if (i != _pfds.size() - 1) _pfds[i] = _pfds.back();
						_pfds.pop_back();
						--current_size;
						--i;
						continue;
					}
					
				}
			}
		}
	}
}

void ServerManager::addPfd(int fd)
{
	pollfd	pfd;
	pfd.fd = fd; 
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pfds.push_back(pfd);
}