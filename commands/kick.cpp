#include "Server.hpp"
#include <limits>

/*
Hexchat sends:
KICK localhost #channel :user reason reason reason reason
*/

void	Server::_kickUserFromChannel(Client &kicked, Channel &channel, const std::string &reason) const
{
	std::string	message;
	message = HEX_INFO + " You have been kicked from the channel '" + channel.getName() + "'";
	if (reason.length() > 0)
		message += " for the following reason: " + reason + '\n';
	else
		message += '\n';
	kicked.leaveChannel(channel.getName());
	channel.deleteUsername(kicked.getUsername().second);
	_sendMessageToClient(kicked, message);
	message = HEX_INFO + " User '" + kicked.getUsername().second + "' has been kicked from the channel '" + channel.getName() + "'";
	if (reason.length() > 0)
		message += " for the following reason: " + reason + '\n';
	else
		message += '\n';
	_sendMessageToChannel(channel, message);
}

std::string	Server::_extractReason(std::istringstream &iss) const
{
	std::string	extractedReason;

	std::getline(iss, extractedReason);
	return (extractedReason);
}

bool	Server::_isUserOp(const Client &client, const std::string &channelName)
{
	if (client.getUsername().second != _allChannels[channelName].getOp())
	{
		_sendMessageToClient(client, HEX_INFO + " You are not operator of this channel\n");
		return (false);
	}
	return (true);
}

void	Server::_kick(std::istringstream &iss, Client &client)
{
	std::string	channelName;
	std::string	username;
	std::string	reason;
	int			clientIndex;

	iss.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // no '#' detected
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: /kick <#channel> <username> <reason>\n");
		return ;
	}
	iss >> channelName;
	channelName.insert(0, 1, '#');
	
	if (_doesChannelExist(client, channelName) == false || _isUserOp(client, channelName) == false)
		return ;

	iss.ignore(std::numeric_limits<std::streamsize>::max(), ':'); // no ':' detected
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: /kick <#channel> <username> <reason>\n");
		return ;
	}
	iss >> username;

	if (_allChannels[channelName].isClientMember(username) == false)
	{
		_sendMessageToClient(client, HEX_INFO + " This user is not a member of this channel\n");
		return ;
	}
	iss.ignore(1); // jumps the space after username
	reason = _extractReason(iss);
	clientIndex = _getClientIndex(username);
	_kickUserFromChannel(_allClients[clientIndex], _allChannels[channelName], reason);
}
