#include "Server.hpp"

void	Server::_disconnectClientFromAllChannels(const std::vector<std::string> &joinedChannelsNames, const std::string &username)
{
	while (joinedChannelsNames.size() != 0)
	{
		if (_allChannels[joinedChannelsNames[0]].isClientOp(username) == true) // user was op on this channel
			_shutdownChannel(joinedChannelsNames[0]);
		else // user was a regular member of this channel
		{
			_sendMessageToChannel(this->_allChannels[joinedChannelsNames[0]], HEX_INFO + " User '" + username + "' has disconnected from this channel\n");
			this->_allChannels[joinedChannelsNames[0]].deleteUsername(username);
		}
	}
/*
	for (std::vector<std::string>::size_type i = 0; i < joinedChannelsNames.size(); i++)
	{
		if (_allChannels[joinedChannelsNames[i]].getOp() == username) // user was op on this channel
		{
			_shutdownChannel(joinedChannelsNames[i]);
			continue ;
		}
		else // user was a regular member of this channel
		{
			_sendMessageToChannel(this->_allChannels[joinedChannelsNames[i]], HEX_INFO + " User '" + username + "' has disconnected from this channel\n");
			this->_allChannels[joinedChannelsNames[i]].deleteUsername(username);
		}
	}
*/
}

void	Server::_quit(Client &client)
{
	int	i = _getClientIndex(client.getUsername().second);

	std::cout << "Client '" << client.getUsername().second << "' has been disconnected from the server" << std::endl;
	this->_disconnectClientFromAllChannels(client.getJoinedChannelsNames(), client.getUsername().second);
	client.closeSocket();
	client.clearJoinedChannelsNames();
	this->_allClients.erase(this->_allClients.begin() + i);
	FD_CLR(client.getSocket(), &this->_readfds);
	this->_maxFd = 0;
	this->_setMaxFd();
}
