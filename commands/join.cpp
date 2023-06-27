#include "Server.hpp"

void	Server::_createChannel(const std::string &channel, Client &client)
{
	Channel	newChannel(channel, client.getUsername().second);

	newChannel.addClient(client);
	_allChannels.insert(_allChannels.end(), std::make_pair(channel, newChannel));
}

void	Server::_createChannel(const std::string &channel, const std::string &password, Client &client)
{
	Channel	newChannel(channel, password, client.getUsername().second);

	newChannel.addClient(client);
	_allChannels.insert(_allChannels.end(), std::make_pair(channel, newChannel));
}

bool	Server::_isChannelNameValid(const std::string &channel) const
{
	if (channel[0] != '#')
	{
		std::cerr << "Channel name must start with a '#' symbol" << std::endl;
		return (false);
	}
	for (std::string::size_type i = 0; i < channel.length(); i++)
	{
		if (channel[i] == ',' || channel[i] == ' ')
		{
			std::cerr << "Channel name can not contain a comma" << std::endl;
			return (false);
		}
	}
	return (true);
}

void	Server::_join(std::istringstream &ss, Client &client)
{
	std::map<std::string, Channel>::iterator	it;
	std::string	channel;
	std::string	password;
	
	ss >> channel;
	if (_isChannelNameValid(channel) == false)
		return ;

	ss >> password;

	it = _allChannels.find(channel);
	if (it == _allChannels.end()) // this channel name does not exist. Must create it
	{
		if (ss.eof() == false) // this channel will have a password
			_createChannel(channel, password, client);
		else // this channel is public
			_createChannel(channel, client);
		_sendMessageToClient(client, HEX_INFO + " You created the channel " + HEX_BOLD + channel + HEX_RESET + "\n");
	}
	else // this channel name exists. Must join it
	{
		if (it->second.isClientAlreadyMember(client) == true)
		{
			_sendMessageToClient(client, HEX_INFO + " You are already member of the channel " + HEX_BOLD + channel + HEX_RESET + "\n");
			return ;
		}
		if (it->second.getPassword().first == true && password != it->second.getPassword().second)
			_sendMessageToClient(client, HEX_INFO + " Incorrect password. Can not join this channel\n");
		else
		{
			it->second.addClient(client);
			_sendMessageToChannel(it->second, HEX_INFO + ' ' + client.getUsername().second + " joined the channel\n");
		}
	}
}
