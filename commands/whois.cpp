#include "Server.hpp"

void	Server::_whois(std::istringstream &iss, const Client &client) const
{
	std::string id;
	std::string	garbage;

	iss >> id;
	iss >> garbage;
	if (iss.eof() != true)
		_sendMessageToClient(client, HEX_INFO + " Usage: /whois <username>\n");
	else if (id.compare("me") == 0)
		_displayClient(client, client.getUsername().second);
	else
		_displayClient(client, id);
}
