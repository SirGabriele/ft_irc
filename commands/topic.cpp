#include "Server.hpp"

void	Server::_topic(std::istringstream & iss, Client const & client)
{
	std::map<std::string, Channel>::iterator	it;
	std::string									channelStr;

	iss >> channelStr;
	if (iss.eof() == true)
		_sendMessageToClient(client, HEX_INFO + " Usage: /topic <#channel> <subject>\n");
	else if (_isChannelNameValid(channelStr, client) == true)
	{
		it = _allChannels.find(channelStr);
		if (it == _allChannels.end())
			_sendMessageToClient(client, HEX_INFO + " The channel '" + channelStr + "' does not exist\n");
		else if (it->second.isClientMember(client.getUsername().second) == false)
			_sendMessageToClient(client, HEX_INFO + " You are not part of '" + channelStr + "'\n");
		else if (it->second.isClientOp(client.getUsername().second) == false)
			_sendMessageToClient(client, HEX_INFO + " You must be operator of the channel to " + \
				"execute this command\n");
		else if (it->second.isBitSet(TOPIC) == false)
			_sendMessageToClient(client, HEX_INFO + " The TOPIC mode is not activated\n");
		else
			it->second.manageTopicChannel(iss, client);
	}
}
