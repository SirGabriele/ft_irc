#include "Server.hpp"

bool	Server::_authentification(std::string token, std::istringstream & ss, Client & client)
{
	bool	status = false;

	if (token.compare("pass") == 0 || token.compare("PASS") == 0)
	{
		_pass(ss, client);
		status = true;
	}
	else if (token.compare("NICK") == 0)
	{
		if (client.getPassword() == false)
		{
			_sendMessageToClient(client, HEX_INFO + " You must enter the correct password\n");
			return (true);
		}
		_nick(ss, client);
		status = true;
	}
	else if (token.compare("user") == 0 || token.compare("USER") == 0)
	{
		if (client.getPassword() == false)
		{
			_sendMessageToClient(client, HEX_INFO + " You must enter the correct password\n");
			return (true);
		}
		else if (client.getNickname().first == false)
		{
			_sendMessageToClient(client, HEX_INFO + " You must set a nickname\n");
			return (true);
		}
		_user(ss, client);
		status = true;
	}
	if (client.getUsername().second.empty() == false && client.getNickname().second.empty() == false
		&& client.getPassword() == true && client.getAuthentification() == false)
	{
		client.setAuthentification(true);
		_sendMessageToClient(client, HEX_INFO + " You successfully authentificated\n");
	}
	return (status);
}

void	Server::_detectCommand(Client &client)
{
	std::istringstream	ss(client.getInput());
	std::string			token;
	
	std::cout << "--------Detect command--------" <<std::endl;
	ss >> token;
	std::cout << client.getInput() << std::endl;
	if (_authentification(token, ss, client) == true)
		return ;
	if (client.getAuthentification() == false)
		_sendMessageToClient(client, HEX_INFO + " You must set a username, " +
			"a nickname and give the correct password to be able to use commands\n");
	else if (token.compare("PRIVMSG") == 0)
		_privmsg(ss, client);
	else if (token.compare("JOIN") == 0)
		_join(ss, client);
	else if (token.compare("whois") == 0 || token.compare("WHOIS") == 0)
		_whois(ss, client);
	else if (token.compare("channels") == 0 || token.compare("CHANNELS") == 0)
		_displayChannels(client);
	else if (token.compare("QUIT") == 0)
		_disconnectClient(client);
	else
	{
		token = "Unknown command " + token + "\n";
		send(client.getSocket(), token.c_str(), token.length(), MSG_DONTWAIT);
	}
}
