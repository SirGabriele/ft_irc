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
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [+k] <password>\n");
	else
	{
		_password = password;
		_modes |= 1 << PASSWORD;
	}
}

void	Channel::_setOperatorChannel(std::istringstream & iss, Client const & client)
{
	std::string	user;
	std::string	garbage;

	iss >> user;
	if (iss.eof())
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [+o] <user>\n");
	else
	{
		iss >> garbage;
		if (iss.eof() == false)
			_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [+o] <user>\n");
		addOp(client);
	}
}

bool	Channel::_isLimitNumeric(std::string const & limitStr)
{
	for (size_t i = 0; i < limitStr.length(); i++)
	{
		if (std::isdigit(limitStr[i]) == 0)
			return (false);
	}
	return (true);
}

void	Channel::_setUserLimitChannel(std::istringstream & iss, Client const & client)
{
	std::string	limitStr;
	std::string	garbage;
	int			limitInt;

	iss >> limitStr;
	if (iss.eof())
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [+l] <limit>\n");
		return ;
	}
	iss >> limitStr;
	if (iss.eof() == false)
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [+l] <limit>\n");
	else if (_isLimitNumeric(limitStr) == false)
		_sendMessageToClient(client, HEX_INFO + " The limit must be numeric\n");
	else
	{
		limitInt = std::atoi(limitStr.c_str());
		if (limitInt > 50 || limitStr.length() > 2)
			_sendMessageToClient(client, HEX_INFO + " The limit cannot exceed 50\n");
		else
		{
			_modes |= 1 << USER_LIMIT;
			_userLimit = limitInt; 
		}
	}
}

void	Channel::_addOptionToChannel(std::istringstream & iss, const std::string & option, Client const & client)
{
	std::string	garbage;

	if (option.length() > 2 || option.find_first_not_of("itkol", 1) != std::string::npos)
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <optional argument>\n");
	else if (option[1] == 'k')
		_setPasswordChannel(iss, client);
	else if (option[1] == 'o')
		_setOperatorChannel(iss, client);
	else if (option[1] == 'l')
		_setUserLimitChannel(iss, client);
	else if (option[1] == 'i' || option[1] == 't')
	{
		iss >> garbage;
		if (iss.eof() == false)
			_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+]i|t}\n");
		else if (option[1] == 'i')
			_modes |= 1 << INVITE;
		else
			_modes |= 1 << TOPIC;
	}
}