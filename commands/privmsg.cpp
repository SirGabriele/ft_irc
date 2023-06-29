#include "Server.hpp"

void	Server::_sendMessage(const Client & client, const Client & recipient)
{
		size_t		pos = 0;
		
		for (int i = 0; i < 2; i++)
		{
			pos = client.getInput().find_first_of(" 	", pos);
			if (pos == std::string::npos)
				return ;
			pos = client.getInput().find_first_not_of(" 	", pos);
		}
		//Mettre une longeur de message max ?
		_sendMessageToClient(recipient, "From " + client.getNickname().second + ": " + client.getInput().substr(pos));
}

void	Server::_privmsg(std::istringstream & iss, const Client & client)
{
		std::vector<Client>::iterator	it;
		std::string						str;
		std::string						nickname;

		if (client.getNickname().second.empty() == true)
			str = "You have to set a nickname\n";
		else if (client.getUsername().second.empty() == true)
			str = "You have to set a username\n";
		else
		{
			iss >> nickname;
			for (it = _allClients.begin(); it < _allClients.end(); it++)
			{
				if (it->getNickname().second.compare(nickname) == 0)
				{
					_sendMessage(client, *it);
					return ;
				}
			}
			if (nickname.empty() == false)
				str = "user '" + nickname + "' not found\n";
			else
				str = "You must specify who the message is adressed to\n";
		}
		send(client.getSocket(), str.c_str(), str.length(), MSG_DONTWAIT);
}		
