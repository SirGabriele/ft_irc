#include "Server.hpp"

void	Server::_pass(std::istringstream & iss, Client & client)
{
	std::string	password;
	std::string	garbage;
	if (client.getPassword() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " You already authentificated\n");
		return ;
	}

	iss >> password;
	iss >> garbage;
	if (iss.eof() != true)
		_sendMessageToClient(client, HEX_INFO + " Password must contain only one word\n");
	else if (password == _password)
	{
		client.setPassword(true);
		_sendMessageToClient(client, HEX_INFO + " Correct password\n");
	}
	else if (password == BOT_PASS)
	{
		client.setPassword(true);
		client.setNickname("passBot");
		client.setUsername("passBot");
		client.setAuthentification(true);

		int	i = _getClientIndex("passBot");
		_passBot = _allClients[i];
		_allClients.erase(_allClients.begin() + i);
		_maxFd = 0;
		_setMaxFd();
	}
	else
		_sendMessageToClient(client, HEX_INFO + " Incorrect password\n");
}
