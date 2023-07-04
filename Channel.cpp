#include "Channel.hpp"

Channel::Channel(void)
{

}

Channel::Channel(const std::string &name): _name(name), _password(""), _modes(0), _topic("")
{

}

Channel::Channel(const std::string &name, const std::string &password): _name(name), _password(password), _modes(0)
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
		this->_memberNames= src._memberNames;
		this->_allOps = src._allOps;
		this->_name = src._name;
		this->_password = src._password;
		this->_modes = src._modes;
	}
	return (*this);
}

	/*	START OF PUBLIC METHODS	*/
void	Channel::addNewUsername(const std::string &username)
{
	this->_memberNames.push_back(username);
}

bool	Channel::isClientMember(const std::string &username) const
{
	for (std::vector<std::string>::size_type i = 0; i < _memberNames.size(); i++)
	{
		if (_memberNames[i] == username)
			return (true);
	}
	return (false);
}

bool	Channel::isClientOp(const std::string &username) const
{
	for (std::vector<std::string>::size_type i = 0; i < _allOps.size(); i++)
	{
		if (_allOps[i] == username)
			return (true);
	}
	return (false);
}

void	Channel::deleteUsername(const std::string &username)
{
	for (std::vector<std::pair<std::string, int> >::size_type i = 0; i < this->_memberNames.size(); i++)
	{
		if (this->_memberNames[i] == username)
		{
			this->_memberNames.erase(this->_memberNames.begin() + i);
			return ;
		}
	}
}

void	Channel::addOp(Client const & client)
{
	std::string	username = client.getUsername().second;

	if (isClientMember(username) == true)
		this->_allOps.push_back(username);
	else if (isClientOp(username) == false)
		_sendMessageToClient(client, "<" + username + "> does not belong to this channel\n");
}

void	Channel::deleteOp(Client const & client)
{
	for (std::vector<std::string>::size_type i = 0; i < this->_allOps.size(); i++)
	{
		if (_allOps[i] == client.getUsername().second)
		{
			_allOps.erase(_allOps.begin() + i);
			return ;
		}
	}
	_sendMessageToClient(client, "This client is not an operator of this channel\n");
}

void	Channel::clearMemberNames(void)
{
	this->_memberNames.clear();
}

bool	Channel::isBitSet(t_modes option) const
{
	return (_modes >> option & 1);
}

void	Channel::manageOption(std::istringstream & iss, Client const & client)
{
	std::string	option;

	iss >> option;
	if (iss.eof() == true)
	{
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <optional argument>\n");
		return ;
	}

	if (option[0] == '+')
		_addOptionToChannel(iss, option, client);
	else if (option[0] == '-')
		_deleteOptionFromChannel(iss, option, client);
	else
		_sendMessageToClient(client, HEX_INFO + " Usage: MODE <#channel> {[+|-]i|t|k|o|l} <optional argument>\n");
}

void	Channel::_sendMessageToClient(const Client &client, const std::string &message) const
{
	if (send(client.getSocket(), message.c_str(), message.length(), MSG_NOSIGNAL) < 0)
		std::cerr << "Failed send()" << std::endl;
}

	/*	END OF PUBLIC METHODS	*/

	/*	START OF GETTERS	*/
const std::string	&Channel::getPassword(void) const	{return (this->_password);}

const std::string	&Channel::getName(void) const	{return (this->_name);}

int	Channel::getNbMembers(void) const	{return (_memberNames.size());}

const std::vector<std::string>	&Channel::getMemberNames(void) const	{return (this->_memberNames);}

const std::vector<std::string>	&Channel::getOps(void) const	{return (this->_allOps);}

const int	&Channel::getUserLimit(void) const	{return (_userLimit);}
	/*	END OF GETTERS	*/
