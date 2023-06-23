#include "Server.hpp"

void	Server::_user(std::istringstream &ss, Client &client)
{
	std::string	username;

	ss >> username;
	if (ss.eof() == true)
		return ;
	else if (username == client.getUsername())
		_sendMessageToClient(client, HEX_INFO + " This is already your username\n");
	else
	{
		client.setUsername(username);
		_sendMessageToClient(client, HEX_INFO + " Your username have been updated to " + HEX_BOLD + username + HEX_RESET + "\n");
	}
}
