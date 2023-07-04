#include "Server.hpp"

void	Server::_removeClientFromChannel(Client &client, Channel &channel)
{
	std::string	channelName	= channel.getName();

	std::string	clientUsername = client.getUsername().second;
	if (channel.getOps().size() == 1) //last operator left the channel
		_shutdownChannel(channelName);
	else //regular user left the channel
	{	
		client.leaveChannel(channelName);
		channel.deleteUsername(clientUsername);
		_sendMessageToChannel(_allChannels[channelName], HEX_INFO + " User '" + clientUsername + "' left the channel '" + channelName + "'\n");
		_sendMessageToClient(client, HEX_INFO + " You left the channel '" + channelName + "'\n");
	}
}

bool	Server::_doesChannelExist(const Client &client, const std::string &channelName) const
{
	std::map<std::string, Channel>::const_iterator	it = _allChannels.find(channelName);
	
	if (it == _allChannels.end()) //channel does not exist
	{
		_sendMessageToClient(client, HEX_INFO + " This channel does not exist\n");
		return (false);
	}
	return (true);
}

void	Server::_part(std::istringstream &iss, Client &client)
{
	std::string	channelName;

	iss >> channelName;

	std::map<std::string, Channel>::const_iterator	it = _allChannels.find(channelName);
	
	if(_isChannelNameValid(channelName, client) == false)
		return ;
	else if (it == _allChannels.end() || client.isInChannel(channelName) == false)
		_sendMessageToClient(client, HEX_INFO + " You can not leave a channel you have not joined previously\n");
	else
		_removeClientFromChannel(client, _allChannels[channelName]);
}
