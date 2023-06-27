#include "Server.hpp"

void	Server::_detectCommand(Client &client)
{
	std::istringstream	ss(client.getInput());
	std::string			token;
	
	std::cout << "--------Detect command--------" <<std::endl;
	ss >> token;
	std::cout << client.getInput() << std::endl;
	if (token.compare("NICK") == 0)
		_nick(ss, client);
	else if (token.compare("user") == 0 || token.compare("USER") == 0)
		_user(ss, client);
	else if (token.compare("JOIN") == 0)
		_join(ss, client);
	else if (token.compare("whois") == 0 || token.compare("WHOIS") == 0)
		_whois(ss, client);
	else if (token.compare("channels") == 0 || token.compare("CHANNELS") == 0)
		_displayChannels(client);
	else if (token.compare("QUIT") == 0)
		_disconnectClient(client);
}
