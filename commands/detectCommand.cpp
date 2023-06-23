#include "Server.hpp"

void	Server::_detectCommand(Client & client)
{
	std::stringstream	ss(client.getInput());
	std::string			token;

	ss >> token;
	std::cout << "command to process: " << token << std::endl;
	if (token.compare("PASS") == 0)
		_settingPassword(ss, client);
	else if (client.getPassword() == false)
	{
		std::cout << "You have not authenticated yet\n";
		return ;
	}
	if (token.compare("NICK") == 0)
		_settingNickname(ss, client);
	if (token.compare("USER") == 0)
		_settingUsername(ss, client);
	if (token.compare("PRIVMSG") == 0)
		_privmsg(ss);
	if (token.compare("JOIN") == 0)
	{
		//faire fonction join;
		std::cout << "JOIN detected\n";
	}
}
