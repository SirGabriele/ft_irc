#include "Server.hpp"
# include "ircserv.hpp"

Server::Server(void): _password(""), _socket(0), _port(0), _nbClients(0), _maxFd(0)
{

}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server(void)
{
	this->_closeSocket();
	for (std::vector<Client>::size_type i = 0; i < this->_allClients.size(); i++)
	{
		this->_allClients[i].closeSocket();
		this->_allClients.erase(this->_allClients.begin() + i);
	}
	std::cout << "Server is shutting down" << std::endl;
}

Server	&Server::operator=(const Server &src)
{
	static_cast<void>(src);
	return (*this);
}

	/*	START OF PUBLIC METHODS	*/
void	Server::start(int port, const char *password)
{
	this->_port = port;
	this->_password = password;
	this->_initSinValues();

	this->_createSocket();
	
	this->_maxFd = this->_socket;

	FD_ZERO(&this->_readfds);
	FD_ZERO(&this->_writefds);
	FD_ZERO(&this->_exceptfds);
	FD_SET(this->_socket, &this->_readfds);
	FD_SET(this->_socket, &this->_writefds);
	FD_SET(this->_socket, &this->_exceptfds);
	
	this->_setSockOptReuseAddr(); 
	this->_bindSocket();
	this->_listenSocket();

	std::cout << B_HI_GREEN << "Your server has been successfully created" << RESET << std::endl;
}
	/*	END OF PUBLIC METHODS	*/

	/*	START OF PRIVATE METHODS	*/
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

bool	Server::_acceptNewClient(void)
{
	Client				newClient(this->_port);
	struct sockaddr_in	clientSin = newClient.getSin();
	unsigned int		clientSinLength = sizeof(clientSin);
	int					clientSocket;

	clientSocket = accept(this->_socket, reinterpret_cast<struct sockaddr *>(&clientSin), &clientSinLength);
	if (this->_socket == -1)
	{
		this->_closeSocket();
		return (false);
	}
	newClient.setSocket(clientSocket);

	this->_allClients.push_back(newClient);

	FD_SET(clientSocket, &this->_readfds);
	FD_SET(clientSocket, &this->_writefds);
	FD_SET(clientSocket, &this->_exceptfds);
	this->_maxFd = (clientSocket > this->_maxFd) ? clientSocket : this->_maxFd;

	this->_nbClients++;
	std::cout << "New client added" << std::endl;
	return (true);
}

void	Server::_disconnectClient(int socket)
{
	for (std::vector<Client>::size_type i = 0; i < this->_allClients.size(); i++)
	{
		if (this->_allClients[i].getSocket() == socket)
		{
			this->_allClients[i].closeSocket();
			this->_allClients.erase(this->_allClients.begin() + i);
			FD_CLR(socket, &this->_readfds);
			FD_CLR(socket, &this->_writefds);
			FD_CLR(socket, &this->_exceptfds);
			this->_nbClients--;
			this->_maxFd = 0;
			this->_setMaxFd();
			std::cout << "Client has been disconnected" << std::endl;
		}
	}
}

bool	Server::_processInput(int socket, const char *buffer)
{
	int	i = this->_getClientIndex(socket);
	if (i == -1)
	{
		return (false);
	}
	this->_allClients[i].completeInput(buffer);
	if (isInputFull(this->_allClients[i].getInput()) == true) // execute command
	{
		this->_parseInput(this->_allClients[i].getInput());
		this->_allClients[i].resetInput();
	}
	else // a supprimer
	{
		std::cout << "Incomplete command for now. Only have [" << buffer << ']' << std::endl;
	}
	return (true);
}
	/*	END OF PRIVATE METHODS	*/

	/*	START OF GETTERS	*/
int	Server::getSocket(void) const
{
	return (this->_socket);
}

fd_set	Server::getReadFds(void) const
{
	return (this->_readfds);
}

fd_set	Server::getWriteFds(void) const
{
	return (this->_writefds);
}

fd_set	Server::getExceptFds(void) const
{
	return (this->_exceptfds);
}

int	Server::getMaxFd(void) const
{
	return (this->_maxFd);
}

int	Server::_getClientIndex(int socket) const
{
	for (std::vector<Client>::size_type i = 0; i < this->_allClients.size(); i++)
	{
		if (this->_allClients[i].getSocket() == socket)
			return (i);
	}
	return (-1);
}

	/*	END OF GETTERS*/

	/*	START OF SETTERS	*/
void	Server::_setMaxFd(void)
{
	if (this->_allClients.size() == 0)
		this->_maxFd = this->_socket;
	for (std::vector<Client>::size_type i = 0; i < this->_allClients.size(); i++)
	{
		this->_maxFd = (this->_allClients[i].getSocket() > this->_maxFd) ? this->_allClients[i].getSocket() : this->_maxFd;
	}
}
	/*	END OF SETTERS	*/

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
