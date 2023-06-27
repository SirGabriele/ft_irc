#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>

# include "Client.hpp"

class	Channel
{
	public:
		Channel(void);
		Channel(const std::string &, const std::string &);
		Channel(const std::string &, const std::string &, const std::string &);
		~Channel(void);
		Channel(const Channel &src);

		void	addClient(Client &);
		bool	isClientAlreadyMember(const Client &) const;

		void	disconnect(const std::string &);
		void	shutdownChannel(void);

		const std::string					&getName(void) const;
		const std::pair<bool, std::string>	&getPassword(void) const;
		const std::string					&getOp(void) const;
		const std::vector<Client>			&getClients(void) const;

	private:
		Channel	&operator=(const Channel &src);
		std::vector<Client>				_allClients;
		std::string						_name;
		std::pair<bool, std::string>	_password;
		std::string						_op;
};

#endif /*CHANNEL_HPP*/
