#include "Channel.hpp"
#include <cstdlib>

void	Channel::_setPasswordChannel(std::istringstream & iss, Channel & channel, Client const & client)
{
	std::string password;

	if (iss.eof())
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> password;
		channel.setModes(PASSWORD);
		channel.setPassword(password);
	}
}
/*
void	Channel::_unsetOperatorChannel()
{
	it->second.setModes(OPERATOR);
	//a faire avec op vector
}*/

void	Channel::_setUserLimitChannel(std::istringstream & iss, Channel & channel, Client const & client)
{
	std::string	limit;

	if (iss.eof())
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> limit;
		channel.setModes(USER_LIMIT);
		channel.setUserLimit(std::atoi(limit.c_str()));
	}
}

void	Channel::_addOptionToChannel(std::istringstream & iss, std::string & option, \
			  Channel & channel, Client const & client)
{
	if (option.find_first_not_of("itkol", 1) != std::string::npos)
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	if (option.length() == 2 && option.find("it") == std::string::npos)
	{
		if (option[1] == 'k')
			_setPasswordChannel(iss, channel, client);
		/*else if (option[1] == 'o')
			_unsetOperatorChannel();*/
		else if (option[1] == 'l')
			_setUserLimitChannel(iss, channel, client);
	}
	else
	{
		if (option.find('i') != std::string::npos)
		 	channel.setModes(INVITE);
		if (option.find('t') != std::string::npos)
			channel.setModes(TOPIC);
		return ;
	}
	_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
}
