#include "Channel.hpp"

void	Channel::_unsetPasswordChannel(std::istringstream &iss, const Client &client)
{
	std::string	garbage;

	iss >> garbage;
	if (iss.eof() == false)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [-k]\n");
		return ;
	}

	_unsetModes(PASSWORD);
	this->_password = "";
}

void	Channel::_unsetOperatorChannel(std::istringstream & iss, Client const & client)
{
	std::string	user;

	if (iss.eof())
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> user;
		deleteOp(user);
	}
}

void	Channel::_deleteOptionFromChannel(std::istringstream & iss, std::string & option, Client const & client)
{
	std::string	garbage;

	if (option.length() > 2 || option.find_first_not_of("itkol", 1) != std::string::npos)
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else if (option[1] == 'o')
		_unsetOperatorChannel(iss, client);
	else if (option[1] == 'k')
		_unsetPasswordChannel(iss, client);
	else if (option[1] == 'l')
		_unsetModes(USER_LIMIT);
	else if (option[1] == 'i' || option[1] == 't')
	{
		iss >> garbage;

		if (iss.eof() == false)
			_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[-]i|t\n");
		else if (option[1] == 'i')
			_unsetModes(INVITE);
		else
			_unsetModes(TOPIC);
	}
}
