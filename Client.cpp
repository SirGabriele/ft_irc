#include "Client.hpp"

Client::Client(void)
{

}

Client::Client(int port): _username(""), _nickname(""), _input(""), _socket(0), _port(port)
{
	this->_initSinValues();
}

Client::Client(const Client &src)
{
	*this = src;
}

Client::~Client(void)
{

}

Client	&Client::operator=(const Client &src)
{
	if (this != &src)
	{
		this->_sin = src._sin;
		this->_socket = src._socket;
		this->_port = src._port;
		this->_nickname = src._nickname;
		this->_username = src._username;
		this->_input = src._input;
	}
	return (*this);
}

	/*	START OF PUBLIC METHODS	*/
void	Client::closeSocket(void) const
{
	if (close(this->_socket) == -1)
		std::cerr << B_HI_RED << "Error:\n" << RESET << "Failed close(client.socket)" << std::endl;
}

void	Client::completeInput(const char *toAdd)
{
	this->_input += toAdd;
}

void	Client::resetInput(void)
{
	this->_input = "";
}
	/*	END OF PUBLIC METHODS	*/

	/*	START OF PRIVATE METHODS	*/
void	Client::_initSinValues(void)
{
	this->_sin.sin_family = AF_INET;
	this->_sin.sin_port = htons(this->_port);
	this->_sin.sin_addr.s_addr = INADDR_ANY;
}
	/*	END OF PRIVATE METHODS	*/

	/*	START OF GETTERS	*/
struct sockaddr_in	Client::getSin(void) const	{return (this->_sin);}

const std::string	&Client::getNickname(void) const	{return (this->_nickname);}

const std::string	&Client::getUsername(void) const	{return (this->_username);}

const std::string	&Client::getInput(void)	{return (this->_input);}

int	Client::getSocket(void) const	{return (this->_socket);}
	/*	END OF GETTERS	*/

	/*	START OF SETTERS	*/
void	Client::setNickname(const std::string &nickname)	{this->_nickname = nickname;}

void	Client::setUsername(const std::string &username)	{this->_username = username;}

void	Client::setSocket(int socket)	{this->_socket = socket;}
	/*END OF SETTERS	*/

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
