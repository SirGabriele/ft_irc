#include "Server.hpp"

void	Server::_detectCommand(Client &client)
{
	std::istringstream	iss(client.getInput());
	std::string			token;
	
	std::cout << "--------Detect command--------" <<std::endl; // A VIRER----------------------
	iss >> token;
	std::cout << client.getInput() << std::endl;
	if (token.compare("CAP") == 0)
		return ;
	if (token.compare("pass") == 0 || token.compare("PASS") == 0)
		_pass(iss, client);
	else if (token.compare("NICK") == 0)
		_nick(iss, client);
	else if (token.compare("user") == 0 || token.compare("USER") == 0)
		_user(iss, client);
	else if (client.getAuthentification() == false)
		_sendMessageToClient(client, HEX_INFO + " You must set a username, " +
			"a nickname and give the correct password to be able to use commands\n");
	else if (token.compare("PRIVMSG") == 0)
		_privmsg(iss, client);
	else if (token.compare("JOIN") == 0)
		_join(iss, client);
	else if (token.compare("whois") == 0 || token.compare("WHOIS") == 0)
		_whois(iss, client);
	else if (token.compare("channels") == 0 || token.compare("CHANNELS") == 0)
		_displayChannels(iss, client);
//	else if (token.compare("QUIT") == 0)
//		_quit(client);
	else if(token.compare("PART") == 0)
		_part(iss, client);
	else if (token.compare("KICK") == 0)
		_kick(iss, client);
	/*else if (token.compare("INVITE") == 0)
		//invite command
	else if (token.compare("TOPIC") == 0)
		//topic command*/
	else if (token.compare("MODE") == 0)
		_mode(iss, client);
	else
	{
		token = "Unknown command " + token + "\n";
		send(client.getSocket(), token.c_str(), token.length(), MSG_DONTWAIT);
	}
}
