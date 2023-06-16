#include "Server.hpp"

Server::Server(void)
{

}

Server::Server(int port): _port(port)
{
	this->_initSinValues();

	this->_createSocket();

	std::cout << B_HI_GREEN << "Your server has been successfully created" << RESET << std::endl;

	this->_setSockOptReuseAddr(); 
	this->_bindSocket();
	this->_listenSocket();
}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server(void)
{
	this->_closeSocket();
	std::cout << "Server is shutting down" << std::endl;
}

Server	&Server::operator=(const Server &src)
{
	static_cast<void>(src);
	return (*this);
}

void	Server::_initSinValues(void)
{
	this->_sin.sin_family = AF_INET;
	this->_sin.sin_port = htons(this->_port);
	this->_sin.sin_addr.s_addr = INADDR_ANY;
}

void	Server::_createSocket(void)
{
	struct protoent	*proto = getprotobyname("tcp");

	if (proto == NULL)
		throw Error("Failed getprotobyname()");

	this->_socket = socket(AF_INET, SOCK_STREAM, proto->p_proto);

	if (this->_socket == -1)
		throw Error("Failed socket()");
}

void	Server::_setSockOptReuseAddr(void) const
{
	int	reuse = 1;

	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
	{
		this->_closeSocket();
		throw Error("Failed setsockopt()");
	}
}

void	Server::_bindSocket(void) const
{
	if (bind(this->_socket, reinterpret_cast<const struct sockaddr *>(&this->_sin), sizeof(this->_sin)) == -1)
	{
		this->_closeSocket();
		throw Error("Failed bind()");
	}
}

void	Server::_listenSocket(void) const
{
	if (listen(this->_socket, MAX_PENDING_CON) == -1)
	{
		this->_closeSocket();	
		throw Error("Failed listen()");
	}
}

void	Server::_closeSocket(void) const
{
	if (close(this->_socket) == -1)
		std::cerr << B_HI_RED << "Error:\n" << RESET << "Failed close(server.socket)" << std::endl;
}

/*int	Server::acceptCon(void)
{
	this->_allClients
}*/

int	Server::getSocket(void) const
{
	return (this->_socket);
}

	/*	START OF EXCEPTIONS	*/
Server::Error::Error(const std::string &str) throw(): _errMsg(str)
{

}

Server::Error::~Error(void) throw()
{

}

const char	*Server::Error::what(void) const throw()
{
	return (this->_errMsg.c_str());
}
	/*	END OF EXCEPTIONS	*/
