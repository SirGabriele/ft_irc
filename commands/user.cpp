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
			if (client.getUsername().empty() == true)
				std::cout << "Your username has been set to '" << username << "'\n";
			else if (client.getUsername().empty() == false)
				std::cout << "Your username has been updated to '" << username << "'\n";
			client.setUsername(username);
			return ;
		}
	}
	std::cout << "Incorrect command USER\n";
}
