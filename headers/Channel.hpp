#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>

# include "Client.hpp"
# include "Server.hpp"

class Server;

typedef enum e_modes
{
	INVITE = 0,
	TOPIC = 1,
	PASSWORD = 2,
	OPERATOR = 3,
	USER_LIMIT = 4,
}	t_modes;

class	Channel
{
	public:
		Channel(void);
		Channel(const Channel &src);
		Channel(const std::string &);
		Channel(const std::string &, const std::string &);
		~Channel(void);

		void	addNewUsername(const std::string &);
		void	deleteUsername(const std::string &);
		void	addOp(const std::string &);
		void	deleteOp(const std::string &);
		bool	isClientMember(const std::string &) const;
		bool	isClientOp(const std::string &) const;
		void	clearMemberNames(void);
		bool	isBitSet(t_modes option) const;
		void	manageOption(std::istringstream & iss, Channel & channel, Client const & client);

		const std::string					&getName(void) const;
		const std::string					&getPassword(void) const;
		const std::string					&getOp(void) const;
		const std::vector<std::string>		&getMemberNames(void) const;
		const std::vector<std::string>		&getOps(void) const;
		const int							&getUserLimit(void) const;

		void								setPassword(std::string password);
		void								setModes(t_modes option);
		void								setUserLimit(int limit);
		void								unsetModes(t_modes option);

	private:
		Channel							&operator=(const Channel &src);
		std::vector<std::string>		_memberNames;
		std::vector<std::string>		_allOps;
		std::string						_name;
		std::string						_password;
		int								_modes;
		int								_userLimit;

		void		_setPasswordChannel(std::istringstream & iss, Channel & channel, Client const & client);
		void		_setUserLimitChannel(std::istringstream & iss, Channel & channel, Client const & client);
		void		_addOptionToChannel(std::istringstream & iss, std::string & option, Channel & channel, Client const & client);
		void		_unsetOperatorChannel(std::istringstream & iss, Channel & channel, Client const & client);
		void		_deleteOptionFromChannel(std::istringstream & iss, std::string & option, Channel & channel, Client const & client);
		void		_sendMessageToClient(const Client &, const std::string &) const;
};

#endif /*CHANNEL_HPP*/
