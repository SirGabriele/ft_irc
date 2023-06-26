#include "Channel.hpp"

Channel::Channel(void)
{

}

Channel::Channel(const std::string &name): _name(name), _password(false, "")
{

}

Channel::Channel(const std::string &name, const std::string &password): _name(name), _password(true, password)
{

}

Channel::Channel(const Channel &src)
{
	*this = src;
}

Channel::~Channel(void)
{

}

Channel	&Channel::operator=(const Channel &src)
{
	if (this != &src)
	{
		this->_allClients = src._allClients;
		this->_name = src._name;
		this->_password = src._password;
	}
	return (*this);
}

	/*	START OF PUBLIC METHODS	*/
void	Channel::addClient(const Client &client)
{
	this->_allClients.push_back(client);
}

bool	Channel::isClientAlreadyMember(const Client &client) const
{
	for (std::vector<Client>::const_iterator it = this->_allClients.begin(); it != this->_allClients.end(); it++)
	{
		if (it->getUsername() == client.getUsername())
			return (true);
	}
	return (false);
}
	/*	END OF PUBLIC METHODS	*/

	/*	START OF GETTERS	*/
const std::pair<bool, std::string>	&Channel::getPassword(void) const
{
	return (this->_password);
}

const std::string	&Channel::getName(void) const
{
	return (this->_name);
}
	/*	END OF GETTERS	*/
