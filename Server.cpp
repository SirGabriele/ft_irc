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
	if (this != &src)
	{
		this->_allChannels = src._allChannels;
		this->_allClients = src._allClients;
		this->_usernameList = src._usernameList;
		this->_sin = src._sin;
		this->_password = src._password;
		this->_readfds = src._readfds;
		this->_writefds = src._writefds;
		this->_socket = src._socket;
		this->_port = src._port;
		this->_nbClients = src._nbClients;
		this->_maxFd = src._maxFd;
	}
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
	FD_SET(this->_socket, &this->_readfds);
	FD_SET(this->_socket, &this->_writefds);
	
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

void	Server::_acceptNewClient(void)
{
	Client				newClient(this->_port);
	struct sockaddr_in	clientSin = newClient.getSin();
	unsigned int		clientSinLength = sizeof(clientSin);
	int					clientSocket;

	clientSocket = accept(this->_socket, reinterpret_cast<struct sockaddr *>(&clientSin), &clientSinLength);
	if (this->_socket == -1)
	{
		this->_closeSocket();
		std::cerr << "Failed accept()" << std::endl;
		return ;
	}
	newClient.setSocket(clientSocket);

	this->_allClients.push_back(newClient);

	FD_SET(clientSocket, &this->_readfds);
	FD_SET(clientSocket, &this->_writefds);
	this->_maxFd = (clientSocket > this->_maxFd) ? clientSocket : this->_maxFd;
	this->_nbClients++;
	std::cout << "New client '" << newClient.getUsername().second << "' added" << std::endl;
}

void	Server::_processInput(int socket, const char *buffer)
{
	int	i = this->_getClientIndex(socket);
	if (i == -1)
	{
		std::cerr << "Failed to get client's index" << std::endl;
		return ;
	}
	this->_allClients[i].completeInput(buffer);

	std::string::size_type j = this->_allClients[i].getInput().find_first_of('\n', 0);
	if (j != std::string::npos) // execute command
	{
		this->_detectCommand(this->_allClients[i]);
		if (static_cast<std::vector<Client>::size_type>(i) < this->_allClients.size())
			this->_allClients[i].resetInput();
	}
	else // a supprimer
	{
		std::cout << "Incomplete command for now. Only have [" << buffer << ']' << std::endl;
	}
}

void	Server::_sendMessageToClient(const Client &client, const std::string &message) const
{
	if (send(client.getSocket(), message.c_str(), message.length(), MSG_NOSIGNAL) < 0)
		std::cerr << "Failed send()" << std::endl;
}

void	Server::_sendMessageToChannel(const Channel &channel, const std::string &message) const
{
	std::vector<Client>::const_iterator	it = channel.getClients().begin();

	while (it != channel.getClients().end())
	{
		if (send(it->getSocket(), message.c_str(), message.length(), 0) < 0)
			std::cerr << "Failed send()" << std::endl;
		it++;
	}
}

void	Server::_displayClient(const Client &client, const std::string &username) const
{
	std::string	message;
	int i = _getClientIndex(username);

	if (i == -1)
	{
		std::cerr << "Failed to get client's index" << std::endl;
		return ;
	}

	Client	toFind = this->_getClient(i);

	if (toFind.getUsername().first == true)
	{
		message = HEX_BOLD + "Username : " + HEX_RESET + toFind.getUsername().second + '\n';
		if (toFind.getNickname().first == true)
			message += HEX_BOLD + "Nickname : " + HEX_RESET + toFind.getNickname().second + '\n';
		_sendMessageToClient(client, message);
	}
}

void	Server::_shutdownServer(void)
{
	for (std::vector<Client>::size_type i = 0; i < this->_allClients.size(); i++)
	{
		this->_disconnectClient(this->_allClients[i]);
	}
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

int	Server::_getClientIndex(const std::string &username) const
{
	for (std::vector<Client>::size_type i = 0; i < this->_allClients.size(); i++)
	{
		if (this->_allClients[i].getUsername().second == username)
			return (i);
	}
	return (-1);
}

const Client	&Server::_getClient(int index) const
{
	return (this->_allClients[index]);
}
/*const Channel	&Server::getChannel(const std::string &name) const
{
	std::map<std::string, Channel>::iterator	it = this->_allChannels.find(name);
}*/

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
