#include "Server.hpp"

void	Server::_settingUsername(std::stringstream & ss, Client & client)
{
	std::string	username;
	std::string	str;
	size_t		pos;

	pos = client.getInput().find_first_of(" ");
	if (pos != std::string::npos)
	{
		pos = client.getInput().find_first_of(" ", pos + 1);
		if (pos == std::string::npos)
		{
			ss >> username;
			if (client.getUsername().empty() == true)
				str = "Your username has been set to '" + username + "'\n";
			else
				str = "Your username has been updated to '" + username + "'\n";
			client.setUsername(username);
			send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
			return ;
		}
	}
	str = "Incorrect command USER\n";
	send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
}
