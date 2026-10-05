#include "ListeningSocket.hpp"

HDE::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklog)
	: BindingSocket(domain, service, protocol, port, interface)
	{	
		backlog = bklog;
		listen(get_sock(), backlog);
		start_listening();
		test_connection(listening);
	}

void HDE::ListeningSocket::start_listening()
{
	listening = listen(get_sock(), backlog);
}