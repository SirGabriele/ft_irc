#include "Channel.hpp"

void	Channel::_unsetOperatorChannel(std::istringstream & iss, Client const & client)
{
	std::string	user;
	std::string	garbage;

	iss >> user;
	if (iss.eof())
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [-o] <user>\n");
	else
	{
		iss >> garbage;
		if (iss.eof() == false)
			_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> [-o] <user>\n");
		deleteOp(client);
		_sendMessageToClient(client, HEX_INFO + " You successfully removed '" + user + "' from operators\n");
	}
}

void	Channel::_deleteOptionFromChannel(std::istringstream & iss, std::string & option, Client const & client)
{
    std::string garbage;

	if (option.find_first_not_of("itkol", 1) != std::string::npos || option.length() > 2)
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else if (option[1] == 'o')
		_unsetOperatorChannel(iss, client);
	else if (option[1] == 'k')
	{
		_modes &= 0 << PASSWORD;
		_sendMessageToClient(client, HEX_INFO + " You successfully turned the password mode off\n");
	}
	else if (option[1] == 'l')
	{
		_modes &= 0 << USER_LIMIT;
		_sendMessageToClient(client, HEX_INFO + " You successfully unset the user limit\n");
	}
	else
	{
        iss >> garbage;

        if (iss.eof() == false)
            _sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[-]i|t\n");
		else if (option[1] == 'i')
		{
			 _modes &= 0 << INVITE;
			_sendMessageToClient(client, HEX_INFO + " You successfully turned the invite mode off\n");
		}
		else
		{
			 _modes &= 0 << TOPIC;
			_sendMessageToClient(client, HEX_INFO + " You successfully turned the topic mode off\n");
		}
	}
}
