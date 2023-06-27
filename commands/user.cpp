#include "Server.hpp"

bool	Server::_isUsernameAlreadyTaken(const std::string &username) const
{
	if (_usernameList.size() == 0)
		return (false);
	for (std::vector<std::string>::size_type i = 0; i < _usernameList.size(); i++)
	{
		if (_usernameList[i] == username)
			return (true);
	}
	return (false);
}

void	Server::_user(std::istringstream &ss, Client &client)
{
	std::string	username;

	ss >> username;
	if (ss.eof() == true)
		return ;
	else if (username == client.getUsername().second)
		_sendMessageToClient(client, HEX_INFO + " This is already your username\n");
	else if (_isUsernameAlreadyTaken(username) == true)
		_sendMessageToClient(client, HEX_INFO + " This username is already taken\n");
	else
	{
		client.setUsername(username);
		_sendMessageToClient(client, HEX_INFO + " Your username have been updated to " + HEX_BOLD + username + HEX_RESET + "\n");
		_usernameList.push_back(username);
	}
}
