#include "Server.hpp"

void	Server::_disconnectClientFromAllChannels(const std::vector<std::string> &joinedChannelsNames, const std::string &username)
{
	for (std::vector<std::string>::size_type i = 0; i < joinedChannelsNames.size(); i++)
	{
		_sendMessageToChannel(this->_allChannels[joinedChannelsNames[i]], HEX_INFO + " User '" + username + "' has disconnected from this channel\n");
		this->_allChannels[joinedChannelsNames[i]].deleteUsername(username);
	}
}

void	Server::_quit(Client &client)
{
	int	i = _getClientIndex(client.getUsername().second);

	std::cout << "Client '" << client.getUsername().second << "' has been disconnected from the server" << std::endl;
	client.closeSocket();
	this->_disconnectClientFromAllChannels(client.getJoinedChannelsNames(), client.getUsername().second);
	client.clearJoinedChannelsNames();
	this->_allClients.erase(this->_allClients.begin() + i);
	FD_CLR(client.getSocket(), &this->_readfds);
	FD_CLR(client.getSocket(), &this->_writefds);
	this->_maxFd = 0;
	this->_setMaxFd();
}
