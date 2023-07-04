#include "Server.hpp"

void	Server::_mode(std::istringstream & iss, Client const & client)
{
	std::map<std::string, Channel>::iterator	it;
	std::string									channel;

	if (iss.eof())
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> channel;
		it = _allChannels.find(channel);
		if (_isChannelNameValid(channel, client) == false)
			_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
		else if (it != _allChannels.end())
		{
			if (it->second.isClientOp(client.getUsername().second) == false)
				_sendMessageToClient(client, "You must be operator of the channel to execute this command\n");
			else
				it->second.manageOption(iss, it->second, client);
		}
		else
			_sendMessageToClient(client, "Error: could not find channel <" + channel + ">\n");
	}
}
