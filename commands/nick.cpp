#include "Server.hpp"

void	Server::_settingNickname(std::stringstream & ss, Client & client)
{
	std::string	nickname;
	std::string	str;
	size_t		pos;

	pos = client.getInput().find_first_of(" ");
	if (pos != std::string::npos)
	{
		pos = client.getInput().find_first_of(" ", pos + 1);
		if (pos == std::string::npos)
		{
			ss >> nickname;
			if (client.getNickname().empty() == true)
				str = "Your nickname has been set to '" + nickname + "'\n";
			else
				str = "Your nickname has been updated to '" + nickname + "'\n";
			client.setNickname(nickname);
			send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
			return ;
		}
	}
	str = "Incorrect command NICK\n";
	send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
}
