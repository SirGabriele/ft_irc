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
		_modes &= 0 << PASSWORD;
	else if (option[1] == 'l')
		_modes &= 0 << USER_LIMIT;
	else
	{
        iss >> garbage;

        if (iss.eof() == false)
            _sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[-]i|t\n");
		else if (option[1] == 'i')
			 _modes &= 0 << INVITE;
		else
			 _modes &= 0 << TOPIC;
	}
}