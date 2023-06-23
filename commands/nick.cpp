#include "Server.hpp"

void	Server::_nick(std::istringstream &ss, Client &client)
{
	std::string	nickname;
	std::string	username;
	std::string	skip;

	ss >> nickname;
	if (nickname == client.getNickname())
		_sendMessageToClient(client, HEX_INFO + " This is already your nickname\n");
	else
	{
		client.setNickname(nickname);
		_sendMessageToClient(client, HEX_INFO + " Your nickname have been updated to " + HEX_BOLD + nickname + HEX_RESET + "\n");
	}
	ss >> skip;
	if (ss.eof() == true)
		return;
	_user(ss, client);
}
