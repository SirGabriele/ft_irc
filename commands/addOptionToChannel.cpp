#include "Channel.hpp"
#include <cstdlib>

void	Channel::_setPasswordChannel(std::istringstream & iss, Client const & client)
{
	std::string password;
	std::string	garbage;

	iss >> password;
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [+k] <password>\n");
		return ;
	}

	iss >> garbage;
	if (iss.eof() == false)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [+k] <password>\n");
		return ;
	}
	else
	{
		_setModes(PASSWORD);
		_setPassword(password);
		_sendMessageToClient(client, HEX_INFO + " You successfully changed the password of this channel");
	}
}

void	Channel::_setUserLimitChannel(std::istringstream & iss, Client const & client)
{
	std::string	limit;

	if (iss.eof())
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> limit;
		_setModes(USER_LIMIT);
		_setUserLimit(std::atoi(limit.c_str()));
	}
}

void	Channel::_addOptionToChannel(std::istringstream & iss, const std::string & option, Client const & client)
{
	std::string	garbage;

	if (option.length() > 2 || option.find_first_not_of("itkol", 1) != std::string::npos)
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <optional argument>\n");
	else if (option[1] == 'k')
		_setPasswordChannel(iss, client);
	/*else if (option[1] == 'o')
		_unsetOperatorChannel();*/
	else if (option[1] == 'l')
		_setUserLimitChannel(iss, client);
	else if (option[1] == 'i' || option[1] == 't')
	{
		iss >> garbage;

		if (iss.eof() == false)
			_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+]i|t}\n");
		else if (option[1] == 'i')
	 		_setModes(INVITE);
		else
			_setModes(TOPIC);
	}
}
