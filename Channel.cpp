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
		this->_memberNames= src._memberNames;
		this->_name = src._name;
		this->_password = src._password;
		this->_op = src._op;
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
	for (std::vector<std::pair<std::string, int> >::size_type i = 0; i < _memberNames.size(); i++)
	{
		if (_memberNames[i] == username)
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

void	Channel::clearMemberNames(void)
{
	this->_memberNames.clear();
}
	/*	END OF PUBLIC METHODS	*/

	/*	START OF GETTERS	*/
const std::pair<bool, std::string>	&Channel::getPassword(void) const	{return (this->_password);}

const std::string	&Channel::getName(void) const	{return (this->_name);}

const std::string	&Channel::getOp(void) const	{return (this->_op);}

const std::vector<std::string>	&Channel::getMemberNames(void) const	{return (this->_memberNames);}
	/*	END OF GETTERS	*/
