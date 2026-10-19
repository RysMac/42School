#include "ServerManager.hpp"
#include "../net/ListenSocket.hpp"
#include "../net/Client.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <map>

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
	del_clients();
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

void ServerManager::del_clients()
{
	std::map<int, Client*>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		delete it->second;
	}
	_clients.clear();
}

void ServerManager::run()
{

	while (true)
	{
		int poll_count = poll(&_pfds[0], _pfds.size(), -1); // -1 must be changed acc to spec ?

		if (poll_count < 0) { throw std::runtime_error("poll failed"); }
		for (size_t i = _pfds.size(); i-- > 0; )
		{
			if (_pfds[i].revents == 0) continue;

			if (i >= _sockets.size() &&_pfds[i].revents & (POLLERR | POLLHUP)) // this cannot happen to listen sockets right? - POLLERR is possible but rare
			{
				std::cout << "Error from client socket. FD: " << _pfds[i].fd << "\n";
				delClient(i);
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
						// Client first, then pfd: every fd in _pfds has a Client in _clients
						try { addClient(client_fd); }
						catch(...)
						{
							std::cerr << "addClient failed, dropping FD: " << client_fd << "\n";
							continue; // addClient already closed client_fd
						}
						try { addPfd(client_fd); }
						catch(...)
						{
							// no pfd exists, so delClient(i) is wrong here (i = listen socket):
							// remove the Client by fd; ~Client closes client_fd
							std::cerr << "addPfd failed, dropping FD: " << client_fd << "\n";
							std::map<int, Client*>::iterator it = _clients.find(client_fd);
							delete it->second;
							_clients.erase(it);
							continue;
						}
					}
				}
			}
			else // B. Obsługa istniejących klientów (Dane wejściowe lub Rozłączenie)
			{
				if (_pfds[i].revents & POLLIN)
				{
					char buffer[BUFFER_SIZE];
					ssize_t bytes_read = recv(_pfds[i].fd, buffer, BUFFER_SIZE, 0);

					if (bytes_read > 0)
					{
						std::cout << "Received from Client: " << _pfds[i].fd << "\n";

						std::map<int, Client*>::iterator it = _clients.find(_pfds[i].fd);
						it->second->save_recv(buffer, (size_t)bytes_read);
						if (it->second->get_recv_done())
							_pfds[i].events = POLLOUT;
					}
					else // this means that recv failed or client disconnected
					{					
						std::cout << "Client disconnected or recv failed. FD: " 
								<< _pfds[i].fd << "\n";
						delClient(i);
						continue;
					}
				}
				else if (_pfds[i].revents & POLLOUT) // we want to send back sth
				{
					std::map<int, Client*>::iterator it = _clients.find(_pfds[i].fd);

					// replace MSG_NOSIGNAL <-> signal(SIGPIPE, SIG_IGN) postponed
					ssize_t s = send(_pfds[i].fd,
									it->second->data_to_send(),
									it->second->bytes_to_send(),
									0);
					if ( s > 0)
					{
						it->second->add_sent_bytes((size_t)s);
						if (it->second->get_send_done())
						{
							std::cout << "the whole message was sent \n";
							delClient(i);
							continue;
						}
					}
					else // send failed
					{		
						delClient(i);
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

// Contract: if this throws, everything is already cleaned up (fd closed,
// no Client in _clients). The caller must not close fd again.
void ServerManager::addClient(int fd)
{
	Client* client = NULL;
	try
	{
		client = new Client(fd); // thanks to this client survives needed timelife
		_clients.insert(std::make_pair(fd, client));
	}
	catch(...)
	{
		if (client == NULL)
			close(fd);       // new failed: no Client exists, nobody else owns fd
		else
			delete client;   // insert failed: ~Client closes fd
		throw;               // both paths must tell the caller it failed
	}
}

// TODO: change the name delClient is misleading
void ServerManager::delClient(size_t i)
{
	std::map<int, Client*>::iterator it = _clients.find(_pfds[i].fd);
	if (it != _clients.end())
	{
		delete it->second;
		_clients.erase(it);
	}
	else
	{
		close(_pfds[i].fd);
	}

	if (i != _pfds.size() - 1) _pfds[i] = _pfds.back();
	_pfds.pop_back();
}
