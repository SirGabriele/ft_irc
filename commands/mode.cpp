#include "Server.hpp"

void	Server::_manageOption(std::istringstream & iss, std::map<std::string,
	Channel>::iterator & it, Client const & client)
{
	std::string	option;

	while (!iss.eof())
	{
		iss >> option;
		if (option[0] == '+')
			_addOptionToChannel(iss, option, it, client);
		else if (option[0] == '-')
			_deleteOptionFromChannel(iss, option, it, client);
		else
			_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	}
}

void	Server::_mode(std::istringstream & iss, Client const & client)
{
	std::map<std::string, Channel>::iterator	it;
	std::string	channel;

	//CHECK SI client EST BIEN UN OPERATEUR DU CHANNEL

	if (iss.eof())
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> channel;
		it = _allChannels.find(channel);
		if (it != _allChannels.end())
			_manageOption(iss, it, client);
		else
			_sendMessageToClient(client, "Error: could not find channel <" + channel + ">\n");
	}
}
