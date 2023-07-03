#include "Server.hpp"
#include <limits>

/*
Hexchat sends:
PRIVMSG #channel :1 2 3 4 5 6 7 8 9 10

PRIVMSG username :1 2 3 4 5 6 7 8 9 10
*/

std::string	Server::_extractString(std::istringstream &iss) const
{
	std::string	extractedMessage;

	std::getline(iss, extractedMessage);
	return (extractedMessage);
}

void	Server::_sendToClient(std::istringstream &iss, const std::string &username, const Client & client) const
{
	std::string	message;
	int			recipientIndex;

	iss.ignore(std::numeric_limits<std::streamsize>::max(), ':'); // no ':' detected
	iss >> message;
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: /msg <#channel|username> <message>\n");
		return ;
	}

	recipientIndex = _getClientIndex(username);

	if (recipientIndex == -1)
	{
		_sendMessageToClient(client, HEX_INFO + " This user does not exist\n");
		return ;
	}
	message += _extractString(iss);
	message += '\n';
	_sendMessageToClient(_allClients[recipientIndex], HEX_BOLD + "From " + HEX_RESET + client.getUsername().second + ": " + message);
	_sendMessageToClient(client, HEX_BOLD + "To " + HEX_RESET + username + ": " + message);
}

void	Server::_sendToChannel(std::istringstream &iss, const std::string &channelName, const Client & client) const
{
	std::map<std::string, Channel>::const_iterator	it = _allChannels.find(channelName);
	std::string	message;

	iss.ignore(std::numeric_limits<std::streamsize>::max(), ':'); // no ':' detected
	iss >> message;
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: /msg <#channel|username> <message>\n");
		return ;
	}
	if (it == _allChannels.end())
	{
		_sendMessageToClient(client, HEX_INFO + " This channel does not exist\n");
		return ;
	}
	else if (client.isInChannel(channelName) == false)
	{
		_sendMessageToClient(client, HEX_INFO + " You are not a member of this channel\n");
		return ;
	}
	message += _extractString(iss);
	message += '\n';
	_sendMessageToChannel(it->second, HEX_BOLD + '[' + it->first + "] " + HEX_RESET + client.getUsername().second + ": " + message);
}

void	Server::_privmsg(std::istringstream & iss, const Client & client) const
{
		std::string	id;

		iss >> id;
		if (iss.eof() == true) // command sent is '/msg'
			_sendMessageToClient(client, HEX_INFO + " Usage: /msg <#channel|username> <message>\n");
		else if (id[0] == '#')
			_sendToChannel(iss, id, client);
		else
			_sendToClient(iss, id, client);
}		
