#include "Server.hpp"

void	Server::_pass(std::istringstream & ss, Client & client)
{
	std::string	password;
	std::string	word;

	if (client.getPassword() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " You already authentificated\n");
		return ;
	}

	ss >> password;
	ss >> word;
	while (ss.eof() != true)
	{
		password += ' ';
		password += word;
		ss >> word;
	}
	if (password == _password)
	{
		client.setPassword(true);
		_sendMessageToClient(client, HEX_INFO + " You successfully authentificated\n");
	}
	else
		_sendMessageToClient(client, HEX_INFO + " Incorrect password\n");
}
