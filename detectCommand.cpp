#include "Server.hpp"

void	Server::_detectCommand(Client &client)
{
	std::istringstream	ss(client.getInput());
	std::string			token;
	
	ss >> token;
	std::cout << client.getInput() << std::endl;
	if (token.compare("NICK") == 0)
		_nick(ss, client);
	if (token.compare("user") == 0)
		_user(ss, client);
	if (token.compare("JOIN") == 0)
		_join(ss, client);
}
