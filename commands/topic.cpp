#include "Server.hpp"

void	Server::_topic(std::istringstream & iss, Client const & client)
{
	std::map<std::string, Channel>::iterator	it;
	std::string									channelStr;

	iss >> channelStr;
	if (iss.eof() == true)
		_sendMessageToClient(client, HEX_INFO + " Usage: TOPIC <#channel> [<subject>]\n");
	else if (_isChannelNameValid(channelStr, client) == true)
	{
		it = _allChannels.find(channelStr);
		if (it == _allChannels.end())
			_sendMessageToClient(client, channelStr + " doest not exist\n");
		else if (it->second.isBitSet(TOPIC) == false)
			_sendMessageToClient(client, HEX_BOLD + "[" + _name + "]" + HEX_RESET + \
				" The TOPIC command is not activated\n");
		else
			it->second.manageTopicChannel(iss, client);
	}
}
