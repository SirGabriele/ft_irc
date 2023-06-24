#include "Server.hpp"

void	Server::_settingNickname(std::stringstream & ss, Client & client)
{
	std::string	nickname;
	size_t		pos;

	pos = client.getInput().find_first_of(" ");
	if (pos != std::string::npos)
	{
		pos = client.getInput().find_first_of(" ", pos + 1);
		if (pos == std::string::npos)
		{
			ss >> nickname;
			if (client.getNickname().empty() == true)
				std::cout << "Your nickname has been set to '" << nickname << "'\n";
			else if (client.getNickname().empty() == false)
				std::cout << "Your nickname has been updated to '" << nickname << "'\n";
			client.setNickname(nickname);
			return ;
		}
	}
	std::cout << "Incorrect command NICK\n";
}
