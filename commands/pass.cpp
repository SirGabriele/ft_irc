#include "Server.hpp"

void	Server::_pass(std::istringstream & iss, Client & client)
{
	std::string	password;
	std::string	word;

	if (client.getPassword() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " You already authentificated\n");
		return ;
	}

	iss >> password;
	iss >> word;
	while (iss.eof() != true)
	{
		password += ' ';
		password += word;
		iss >> word;
	}
	if (password == _password)
		client.setPassword(true);
	else
		_sendMessageToClient(client, HEX_INFO + " Incorrect password\n");
}
