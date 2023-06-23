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
			client.setNickname(nickname);
			return ;
		}
	}
	std::cout << "Incorrect command NICK\n";
}
