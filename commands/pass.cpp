#include "Server.hpp"

void	Server::_settingPassword(std::stringstream & ss, Client & client)
{
	std::string	password;
	std::string	str("Incorrect password\n");
	size_t		pos;

	pos = client.getInput().find_first_of(" ");
	if (pos != std::string::npos)
	{
		pos = client.getInput().find_first_of(" ", pos + 1);
		if (pos == std::string::npos)
		{
			ss >> password;
			if (_password.compare(password) == 0)
			{
				client.setPassword(true);
				return ;
			}
		}
	}
	send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
}
