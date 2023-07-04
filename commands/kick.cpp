#include "Server.hpp"
#include <limits>

/*
Hexchat sends:
KICK localhost #channel :user reason reason reason reason

KICK IRC #channel :username reason oui non peut-etre
*/

void	Server::_kickUserFromChannel(Client &kicked, Channel &channel, const std::string &reason)
{
	std::string	message;

	message = HEX_INFO + " You have been kicked from the channel '" + channel.getName() + "'";
	if (reason.length() > 0)
		message += " for the following reason: " + reason + '\n';
	else
		message += '\n';
	if (channel.getOps().size() == 1)
	{
		_shutdownChannel(channel.getName());
		return ;
	}
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

void	Server::_kick(std::istringstream &iss, Client &client)
{
	std::string	channelName;
	std::string	username;
	std::string	reason;
	int			clientIndex;

	iss.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // no '#' detected
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: /kick <#channel> :<username> <reason>\n");
		return ;
	}
	iss >> channelName;
	channelName.insert(0, 1, '#');
	
	if (_doesChannelExist(client, channelName) == false || _allChannels[channelName].isClientOp(client.getUsername().second) == false)
		return ;

	iss.ignore(std::numeric_limits<std::streamsize>::max(), ':'); // no ':' detected
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: /kick <#channel> :<username> <reason>\n");
		return ;
	}
	iss >> username;

	if (_allChannels[channelName].isClientMember(username) == false)
	{
		_sendMessageToClient(client, HEX_INFO + " This user is not a member of this channel\n");
		return ;
	}
	iss.ignore(1); // jumps the space after username
	reason = _extractString(iss);
	clientIndex = _getClientIndex(username);
	_kickUserFromChannel(_allClients[clientIndex], _allChannels[channelName], reason);
}
