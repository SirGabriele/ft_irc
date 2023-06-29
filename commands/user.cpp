#include "Server.hpp"

bool	Server::_isUsernameAlreadyTaken(const std::string &username) const
{
	for (std::vector<Client>::size_type i = 0; i < _allClients.size(); i++)
	{
		if (_allClients[i].getUsername().second == username)
			return (true);
	}
	return (false);
}

void	Server::_userHexchat(std::istringstream &iss, Client &client)
{
	std::string	username;
	
	iss >> username;
	if (username == client.getUsername().second)
		_sendMessageToClient(client, HEX_INFO + " This is already your username\n");
	else if (_isUsernameAlreadyTaken(username) == true)
		_sendMessageToClient(client, HEX_INFO + " This username is already taken\n");
	else
	{
		client.setUsername(username);
		_sendMessageToClient(client, HEX_INFO + " Your username have been updated to '" + username + "'\n");
	}
}

void	Server::_user(std::istringstream &iss, Client &client)
{
	std::string	username;
	std::string	garbage;

	iss >> username;
	iss >> garbage;
	if (iss.eof() == false)
		_sendMessageToClient(client, HEX_INFO + " Usage: /user <username>\n");
	else if (username == client.getUsername().second)
		_sendMessageToClient(client, HEX_INFO + " This is already your username\n");
	else if (_isUsernameAlreadyTaken(username) == true)
		_sendMessageToClient(client, HEX_INFO + " This username is already taken\n");
	else
	{
		client.setUsername(username);
		_sendMessageToClient(client, HEX_INFO + " Your username have been updated to '" + username + "'\n");
	}
}
