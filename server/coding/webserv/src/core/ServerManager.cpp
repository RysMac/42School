#include "ServerManager.hpp"
#include "../net/ListenSocket.hpp"
#include "../net/Client.hpp"
#include "../http/HttpResponse.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <map>
#include <fstream>
#include <cerrno>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

ServerManager::ServerManager(ServerConfig& config) : _config(config)
{
	const std::string host = "0.0.0.0";

	try
	{
		_sockets.reserve(_config.ports.size());
		std::vector<int>::const_iterator pi;
		for (pi = _config.ports.begin(); pi != _config.ports.end(); ++pi) {

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
						it->second->request_save_recv(buffer, (size_t)bytes_read);
						if (it->second->get_request_recv_done())
						{
							it->second->set_response(handle_request(it->second->get_request()).to_string());
							_pfds[i].events = POLLOUT;
						}
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

					// MSG_NOSIGNAL <-> signal(SIGPIPE, SIG_IGN) - remember it
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

HttpResponse ServerManager::handle_request(const HttpRequest& request) const
{
	int status = request.get_status();
	HttpResponse rsp;
	if (status != 0)
	{
		rsp = HttpResponse::make_error(status);
	}
	else if (request.get_method() != "GET")
	{
		// 405 must say which methods are allowed (RFC 9110 §15.5.6)
		rsp = HttpResponse::make_error(405);
		rsp.set_header("Allow", "GET");
	}
	else
	{
		// the target is path + optional "?query"; only the path names a file
		std::string path = request.get_path();
		size_t q = path.find('?');
		if (q != std::string::npos)
			path.erase(q);

		// TODO safety: path is used as the client sent it (no ".." check yet)
		rsp = serve_static(path);
	}
	return rsp;
}

// extension -> Content-Type; without the right type the browser ignores CSS
static std::string mime_type(const std::string& file)
{
	size_t dot = file.rfind('.');
	if (dot == std::string::npos)
		return "application/octet-stream";

	std::string ext = file.substr(dot + 1);
	if (ext == "html" || ext == "htm")	return "text/html";
	if (ext == "css")					return "text/css";
	if (ext == "js")					return "application/javascript";
	if (ext == "png")					return "image/png";
	if (ext == "jpg" || ext == "jpeg")	return "image/jpeg";
	if (ext == "gif")					return "image/gif";
	if (ext == "ico")					return "image/x-icon";
	if (ext == "txt")					return "text/plain";
	return "application/octet-stream";	// unknown: the browser offers a download
}

// stat() failed: why? (errno is set by stat)
static int stat_error_status()
{
	if (errno == ENOENT || errno == ENOTDIR)
		return 404;
	if (errno == EACCES)
		return 403;
	return 500;
}

// path = URL path without the query, always starting with '/'
HttpResponse ServerManager::serve_static(const std::string& path) const
{
	std::string	file = _config.root + path;	// "www" + "/style.css"
	struct stat	st;

	if (stat(file.c_str(), &st) == -1)
		return HttpResponse::make_error(stat_error_status());

	if (S_ISDIR(st.st_mode))
	{
		// "/gallery" -> "/gallery/": else relative links in that page
		// ("photo.png", "../style.css") resolve against the wrong folder
		if (path[path.size() - 1] != '/')
		{
			HttpResponse r = HttpResponse::make_error(301);
			r.set_header("Location", path + "/");
			return r;
		}
		file += _config.index;
		if (stat(file.c_str(), &st) == -1)
			return HttpResponse::make_error(403);	// no index, no autoindex yet
	}

	if (!S_ISREG(st.st_mode))
		return HttpResponse::make_error(403);	// fifo, device, dir named index.html...

	// regular files don't need poll() (subject), so read it all at once
	// TODO: a huge file ends up in memory twice (here and in _out)
	std::ifstream in(file.c_str(), std::ios::in | std::ios::binary);
	if (!in)
		return HttpResponse::make_error(403);	// exists but we can't read it

	std::ostringstream content;
	content << in.rdbuf();		// copies every byte, '\0' included

	HttpResponse r;
	r.set_body(content.str(), mime_type(file));
	return r;
}
