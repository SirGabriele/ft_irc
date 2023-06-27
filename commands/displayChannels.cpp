#include "Server.hpp"

void	Server::_displayChannels(Client &client) const
{
	std::map<std::string, Channel>::const_iterator	it = this->_allChannels.begin();
	std::string										message;

	if (it == this->_allChannels.end())
		message = HEX_INFO + " There is currently no existing channel" + HEX_RESET + '\n';
	else
	{
		message = HEX_INFO + " List of all channels currently existing :" + '\n';

		while (it != this->_allChannels.end())
		{
			message += "- " + it->first + " | Op : " + it->second.getOp() + '\n';
			it++;
		}
	}
	_sendMessageToClient(client, message);
}
