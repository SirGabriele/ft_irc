#include "Server.hpp"

Client *	Server::_getRecipient(std::string username)
{
	std::vector<Client>::iterator	it;

	for (it = _allClients.begin(); it != _allClients.end(); it++)
	{
		if (it->getUsername().second.compare(username) == 0)
			return (&(*it));
	}
	return (NULL);
}

Channel*	Server::_getChannel(std::string channel)
{
	std::map<std::string, Channel>::iterator	it;

	for (it = _allChannels.begin(); it != _allChannels.end(); it++)
	{
		if (it->second.getName().compare(channel) == 0)
			return (&it->second);
	}
	return (NULL);
}

void	Server::_sendMessage(Client & client, Client const & recipient, std::string str)
{
	size_t		pos = 0;

	for (int i = 0; i < 2; i++)
	{
		pos = client.getInput().find_first_of(" 	", pos);
		if (pos == std::string::npos)
			return ;
		pos = client.getInput().find_first_not_of(" 	", pos);
	}
	if (client.getInput().substr(pos)[0] != ':')
		_sendMessageToClient(client, "Correct usage: PRIVMSG <msgtarget> :<message>\n");
	else
		_sendMessageToClient(recipient, str + client.getInput().substr(pos + 1));
}

void	Server::_sendToClient(std::string username, Client & client)
{
		Client *		recipient;
		std::string		str;
		
		recipient = _getRecipient(username);
		str = HEX_BOLD + "From " + HEX_RESET + client.getUsername().second + ": ";
		if (recipient != NULL)
		{
			_sendMessage(client, *recipient, str);
			return ;
		}
		else if (username.empty() == false)
			str = "user '" + username + "' not found\n";
		else
			str = "You must specify a recipient (it can be a channel or a username)\n";
		send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
}

void	Server::_sendToChannel(std::string channel, Client & client)
{
	std::vector<Client>::const_iterator	itClients;
	std::vector<Client>::const_iterator	itClientsEnd;
	Channel	*							channelObject;
	std::string							str;

	channelObject = _getChannel(channel);
	if (channelObject != NULL)
	{
		str = HEX_BOLD + "[" +channel + "] " + HEX_RESET + client.getUsername().second + ": ";
		itClients = channelObject->getClients().begin();
		itClientsEnd = channelObject->getClients().end();
		while (itClients != itClientsEnd)
		{
			if (client.getUsername().second != itClients->getUsername().second)
				_sendMessage(client, *itClients, str);
			itClients++;
		}
		return ;
	}
	else if (channel.empty() == false)
		str = "Channel " + channel + " not found\n";
	else
		str = "You must specify a recipient (it can be a channel or a username)\n";
	send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
}

void	Server::_privmsg(std::istringstream & ss, Client & client)
{
		std::string	id;

		ss >> id;
		if (id[0] == '#')
			_sendToChannel(id, client);
		else
			_sendToClient(id, client);
}		
