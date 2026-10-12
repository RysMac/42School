#include "Client.hpp"
#include <unistd.h>


Client::Client(int fd) : _fd(fd) {};

Client::~Client() { close(_fd); }
