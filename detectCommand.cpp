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
	else if (token.compare("pass") == 0 || token.compare("PASS") == 0)
		_pass(ss, client);
	else if (client.getNickname().first != true || client.getUsername().first != true || client.getPassword() != true)
		_sendMessageToClient(client, HEX_INFO + " You must set a username, a nickname and give the correct password to be able to use commands\n");
	else if (token.compare("JOIN") == 0)
		_join(ss, client);
	else if (token.compare("whois") == 0 || token.compare("WHOIS") == 0)
		_whois(ss, client);
	else if (token.compare("channels") == 0 || token.compare("CHANNELS") == 0)
		_displayChannels(client);
	else if (token.compare("QUIT") == 0)
		_disconnectClient(client);
}
