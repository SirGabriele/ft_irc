#include "Server.hpp"

/*
void	Server::_unsetOperatorChannel()
{
	it->second.setModes(OPERATOR);
	//a faire avec op vector
}*/

void	Server::_deleteOptionFromChannel(std::istringstream & iss, std::string & option, \
			  std::map<std::string, Channel>::iterator & it, Client const & client)
{
	(void)iss; //a supprimer
	if (option.find_first_not_of("itkol", 1) != std::string::npos)
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
	/*else if (option.find('o') != std::string::npos && option.length() == 2)
		_unsetOperatorChannel();*/
	else if (option.find('o') == std::string::npos)
	{
		if (option.find('i') != std::string::npos)
			it->second.unsetModes(INVITE);
		if (option.find('t') != std::string::npos)
			it->second.unsetModes(TOPIC);
		if (option.find('k') != std::string::npos)
			it->second.unsetModes(PASSWORD);
		if (option.find('l') != std::string::npos)
			it->second.unsetModes(USER_LIMIT);
	}
	else
		_sendMessageToClient(client, "Usage: MODE <#channel> {[+|-]i|t|k|o|l} <argument>\n");
}
