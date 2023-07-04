#include "Server.hpp"
#include <cstdlib>

void	Server::_setPasswordChannel(std::istringstream & iss, \
				std::map<std::string, Channel>::iterator & it, Client const & client)
{
	std::string password;

	if (iss.eof())
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> password;
		it->second.setModes(PASSWORD);
		it->second.setPassword(password);
	}
}
/*
void	Server::_unsetOperatorChannel()
{
	it->second.setModes(OPERATOR);
	//a faire avec op vector
}*/

void	Server::_setUserLimitChannel(std::istringstream & iss, \
			  std::map<std::string, Channel>::iterator & it, Client const & client)
{
	std::string	limit;

	if (iss.eof())
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else
	{
		iss >> limit;
		it->second.setModes(USER_LIMIT);
		it->second.setUserLimit(std::atoi(limit.c_str()));
	}
}

void	Server::_addOptionToChannel(std::istringstream & iss, std::string & option, \
			  std::map<std::string, Channel>::iterator & it, Client const & client)
{
	if (option.find_first_not_of("itkol", 1) != std::string::npos)
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	else if (option[1] == 'k' && option.length() == 2)
		_setPasswordChannel(iss, it, client);
	/*else if (option[1] == 'o' && option.length() == 2)
		_unsetOperatorChannel();*/
	else if (option[1] == 'l' && option.length() == 2)
		_setUserLimitChannel(iss, it, client);
	else if (option.find("kol") == std::string::npos)
	{
		if (option.find('i') != std::string::npos)
		 	it->second.setModes(INVITE);
		if (option.find('t') != std::string::npos)
			it->second.setModes(TOPIC);
	}
	else
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
}
