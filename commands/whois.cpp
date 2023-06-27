#include "Server.hpp"

void	Server::_whois(std::istringstream &ss, Client &client) const
{
	std::string id;

	ss >> id;
	if (id.compare("me") == 0)
		_displayClient(client, client.getUsername().second);
	else
		_displayClient(client, id);
}
