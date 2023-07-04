#include "Server.hpp"

void	Server::_createChannel(const std::string &channel, Client &client)
{
	Channel	newChannel(channel);

	newChannel.addNewUsername(client.getUsername().second);
	newChannel.addOp(client.getUsername().second);
	client.addJoinedChannelName(newChannel.getName());
	_allChannels.insert(_allChannels.end(), std::make_pair(channel, newChannel));
}

void	Server::_createChannel(const std::string &channel, const std::string &password, Client &client)
{
	Channel	newChannel(channel, password);

	newChannel.addNewUsername(client.getUsername().second);
	newChannel.addOp(client.getUsername().second);
	client.addJoinedChannelName(newChannel.getName());
	_allChannels.insert(_allChannels.end(), std::make_pair(channel, newChannel));
}

bool	Server::_isChannelNameValid(const std::string &channel, const Client &client) const
{
	if (channel[0] != '#' || channel.length() < 2)
	{
		_sendMessageToClient(client, HEX_INFO + " Channel name must start with a '#' symbol followed by a non-empty string\n");
		return (false);
	}
	for (std::string::size_type i = 0; i < channel.length(); i++)
	{
		if (channel[i] == ',' || channel[i] == ' ')
		{
			_sendMessageToClient(client, HEX_INFO + " Channel name can not contain commas or spaces\n");
			return (false);
		}
	}
	return (true);
}

void	Server::_join(std::istringstream &iss, Client &client)
{
	std::map<std::string, Channel>::iterator	it;
	std::string	channel;
	std::string	password;
	
	iss >> channel;
	if (_isChannelNameValid(channel, client) == false)
		return ;

	iss >> password;

	it = _allChannels.find(channel);
	if (it == _allChannels.end()) // channel name does not exist. Must create it
	{
		if (iss.eof() == false) // this channel will have a password
			_createChannel(channel, password, client);
		else // this channel is public
			_createChannel(channel, client);
		_allChannels[channel].addNewUsername(client.getUsername().second);
		client.addJoinedChannelName(_allChannels[channel].getName());
		_sendMessageToClient(client, HEX_INFO + " You created the channel '" + HEX_BOLD + channel + HEX_RESET + "'\n");
	}
	else // this channel name exists. Must join it
	{
		if (it->second.isClientMember(client.getUsername().second) == true)
			_sendMessageToClient(client, HEX_INFO + " You are already member of the channel " + HEX_BOLD + channel + HEX_RESET + "\n");
		else if (it->second.isBitSet(PASSWORD) == false && password.length() != 0)
			_sendMessageToClient(client, HEX_INFO + " This is a public channel, you must not provide a password to join it\n");
		else if (it->second.isBitSet(PASSWORD) == true && password.length() == 0)
			_sendMessageToClient(client, HEX_INFO + " This is a private channel that requires the correct password to join\n");
		else if (it->second.isBitSet(PASSWORD) == true && password != it->second.getPassword())
			_sendMessageToClient(client, HEX_INFO + " Incorrect password. Can not join this channel\n");
		else
		{
			it->second.addNewUsername(client.getUsername().second);
			client.addJoinedChannelName(it->first);
			_sendMessageToChannel(it->second, HEX_INFO + ' ' + client.getUsername().second + " joined the channel\n");
		}
	}
}
