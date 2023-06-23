#include "Server.hpp"

void	Server::_settingUsername(std::stringstream & ss, Client & client)
{
	std::string	username;
	size_t		pos;

	pos = client.getInput().find_first_of(" ");
	if (pos != std::string::npos)
	{
		pos = client.getInput().find_first_of(" ", pos + 1);
		if (pos == std::string::npos)
		{
			ss >> username;
			client.setUsername(username);
			return ;
		}
	}
	std::cout << "Incorrect command USER\n";
}
