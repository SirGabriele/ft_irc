#include "Client.hpp"

Client::Client(void)
{

}

Client::Client(int port): _socket(0), _port(port)
{
	this->_initSinValues();
}

Client::Client(const Client &src)
{
	*this = src;
}

Client::~Client(void)
{
	this->_closeSocket();
}

Client	&Client::operator=(const Client &src)
{
	static_cast<void>(src);
	return (*this);
}

void	Client::_initSinValues(void)
{
	this->_sin.sin_family = AF_INET;
	this->_sin.sin_port = htons(this->_port);
	this->_sin.sin_addr.s_addr = INADDR_ANY;
}

void	Client::_closeSocket(void) const
{
	if (close(this->_socket) == -1)
		std::cerr << B_HI_RED << "Error:\n" << RESET << "Failed close(client.socket)" << std::endl;
}

struct sockaddr_in	Client::getSin(void) const
{
	return (this->_sin);
}

int	Client::getSocket(void) const
{
	return (this->_socket);
}

void	Client::setSocket(int socket)
{
	this->_socket = socket;
}

	/*	START OF EXCEPTIONS	*/
Client::Error::Error(const std::string &str) throw(): _errMsg(str)
{

}

Client::Error::~Error(void) throw()
{

}

const char	*Client::Error::what(void) const throw()
{
	return (this->_errMsg.c_str());
}
	/*	END OF EXCEPTIONS	*/
