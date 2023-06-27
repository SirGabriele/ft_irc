#include "Server.hpp"

void	Server::_disconnectFromAllChannels(const std::vector<std::string> &clientChannels, const std::string &username)
{
	std::string	channelName;
	for (std::vector<std::string>::size_type i = 0; i < clientChannels.size(); i++)
	{
		_sendMessageToChannel(this->_allChannels[channelName], HEX_INFO + " User '" + username + "' has disconnected from this channel\n");
		channelName = clientChannels[i];
		this->_allChannels[channelName].disconnect(username);
	}
}

void	Server::_disconnectClient(Client &client)
{
	int	i = _getClientIndex(client.getUsername().second);

	std::cout << "Client '" << client.getUsername().second << "' has been disconnected from the server" << std::endl;
	client.closeSocket();
	this->_disconnectFromAllChannels(client.getAllChannels(), client.getUsername().second);
	this->_allClients.erase(this->_allClients.begin() + i);
	FD_CLR(client.getSocket(), &this->_readfds);
	FD_CLR(client.getSocket(), &this->_writefds);
	this->_nbClients--;
	this->_maxFd = 0;
	this->_setMaxFd();
}
