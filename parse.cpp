#include "Server.hpp"

bool    Server::_detectCommand(const std::string &input) const
{
	std::stringstream    ss(input);
	std::string            token;
	
	ss >> token;
	std::cout << "command to process: " << token << std::endl;
	if (token.compare("PRIVMSG") == 0)
		{
		//faire fonction privmsg;
		std::cout << "PRIVMSG detected\n";
	}
	if (token.compare("JOIN") == 0)
	{
		//faire fonction join;
		std::cout << "JOIN detected\n";
	}
	return (true);
}
