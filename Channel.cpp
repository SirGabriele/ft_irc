#include "Channel.hpp"

Channel::Channel(void)
{

}

Channel::Channel(const std::string &name, const std::string &op): _name(name), _password(false, ""), _op(op)
{

}

Channel::Channel(const std::string &name, const std::string &password, const std::string &op): _name(name), _password(true, password), _op(op)
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
		this->_op = src._op;
	}
	return (*this);
}

	/*	START OF PUBLIC METHODS	*/
void	Channel::addClient(Client &client)
{
	this->_allClients.push_back(client);
	client.addChannel(this->_name);
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

void	Channel::disconnect(const std::string &username)
{
	for (std::vector<Client>::size_type i = 0; i < this->_allClients.size(); i++)
	{
		if (this->_allClients[i].getUsername().second == username)
		{
			this->_allClients.erase(this->_allClients.begin() + i);
			return ;
		}
	}
}
	/*	END OF PUBLIC METHODS	*/

	/*	START OF GETTERS	*/
const std::pair<bool, std::string>	&Channel::getPassword(void) const	{return (this->_password);}

const std::string	&Channel::getName(void) const	{return (this->_name);}

const std::string	&Channel::getOp(void) const	{return (this->_op);}

const std::vector<Client>	&Channel::getClients(void) const	{return (this->_allClients);}
	/*	END OF GETTERS	*/
