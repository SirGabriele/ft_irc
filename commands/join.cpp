#include "Server.hpp"

void	Server::_createChannel(const std::string &channel, Client &client)
{
	Channel	newChannel(channel, client.getUsername().second);

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
	std::string									channel;
	std::string									password;
	
	iss >> channel;
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: /join <#channel> <optional password>\n");
		return ;
	}

	iss >> password;
	if (_isChannelNameValid(channel, client) == false)
		return ;

	it = _allChannels.find(channel);

	if (it == _allChannels.end()) // this channel does not exist. Must create it
	{
		if (password.length() != 0)
			_sendMessageToClient(client, HEX_INFO + " You can not set a password while creating a channel\n");
		else
		{
			_createChannel(channel, client);
			_sendMessageToClient(client, HEX_INFO + " You created the channel '" + HEX_BOLD + channel + HEX_RESET + "'\n");
		}
	}
	else // this channel exists. Try to join it
	{
		if (it->second.isClientMember(client.getUsername().second) == true)
			_sendMessageToClient(client, HEX_INFO + " You are already member of this channel\n");
		else if (it->second.isBitSet(PASSWORD) == false && password.length() != 0)
			_sendMessageToClient(client, HEX_INFO + " This is a public channel, you must not provide a password to join it\n");
		else if (it->second.isBitSet(PASSWORD) == true && password.length() == 0)
			_sendMessageToClient(client, HEX_INFO + " This is a private channel that requires the correct password to join\n");
		else if (it->second.isBitSet(PASSWORD) == true && password != it->second.getPassword())
			_sendMessageToClient(client, HEX_INFO + " Incorrect password. Can not join this channel\n");
		else if (it->second.isBitSet(INVITE) == true && _allChannels[channel].isClientInvited(client.getUsername().second) == false)
			_sendMessageToClient(client, HEX_INFO + " This channel is in invite mode only and you have not been invited\n");
		else if (it->second.isBitSet(USER_LIMIT) == true && static_cast<int>(_allChannels[channel].getMemberNames().size()) > _allChannels[channel].getUserLimit())
			_sendMessageToClient(client, HEX_INFO + " This channel is currently full\n");
		else
		{
			it->second.addNewUsername(client.getUsername().second);
			client.addJoinedChannelName(it->first);
			_sendMessageToChannel(it->second, HEX_INFO + ' ' + client.getUsername().second + " joined the channel\n");
			if (it->second.isBitSet(TOPIC) == true)
				_sendMessageToClient(client, HEX_INFO + " The topic of this channel is: " + it->second.getTopic());
			if (it->second.isBitSet(INVITE) == true)
				it->second.deleteInvitedUser(client.getUsername().second);
		}
	}
}
