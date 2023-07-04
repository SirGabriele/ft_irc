#include "Channel.hpp"

void	Channel::_unsetOperatorChannel(std::istringstream & iss, Channel & channel, Client const & client)
{
	std::string	user;

	if (iss.eof())
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> user;
		channel.deleteOp(user);
		channel.unsetModes(OPERATOR);
	}
}

void	Channel::_deleteOptionFromChannel(std::istringstream & iss, std::string & option, \
			  Channel & channel, Client const & client)
{
	if (option.find_first_not_of("itkol", 1) != std::string::npos)
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else if (option.find('o') != std::string::npos
	  	&& option.length() == 2 && channel.isBitSet(INVITE) == true)
		_unsetOperatorChannel(iss, channel, client);
	else
	{
		if (option.find('i') != std::string::npos && channel.isBitSet(INVITE) == true)
			channel.unsetModes(INVITE);
		if (option.find('t') != std::string::npos && channel.isBitSet(TOPIC) == true)
			channel.unsetModes(TOPIC);
		if (option.find('k') != std::string::npos && channel.isBitSet(PASSWORD) == true)
			channel.unsetModes(PASSWORD);
		if (option.find('l') != std::string::npos && channel.isBitSet(USER_LIMIT) == true)
			channel.unsetModes(USER_LIMIT);
		return ;
	}
	_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
}
