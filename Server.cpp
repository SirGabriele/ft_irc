#include "Server.hpp"

Server::Server(void)
{

}

Server::Server(int port): _reuse(1)
{
	struct protoent	*proto = getprotobyname("tcp");

	if (proto == NULL)
		throw Error("Failed getprotobyname()");
	this->_socket = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (this->_socket == -1)
		throw Error("Failed socket()");
	else
		std::cout << B_HI_GREEN << "Your server has been successfully created" << RESET << std::endl;
	
}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server(void)
{

}

Server	&Server::operator=(const Server &src)
{
	if (this != &src)
	{
	
	}
	return (*this);
}

int	Server::getSocket(void) const
{
	return (this->_socket);
}

	/*	START OF EXCEPTIONS	*/
Server::Error::Error(const std::string &str) throw(): _errMsg(str)
{

}

Server::Error::~Error(void)
{

}

const char	*Server::Error::what(void) const throw()
{
	return (this->_errMsg.c_str());
}
	/*	END OF EXCEPTIONS	*/
