#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>

# include "Client.hpp"

class	Channel
{
	public:
		Channel(const std::string &);
		Channel(const std::string &, const std::string &);
		~Channel(void);
		Channel(const Channel &src);

		void	addClient(const Client &);
		bool	isClientAlreadyMember(const Client &) const;

		std::pair<bool, std::string>	getPassword(void) const;
	
	private:
		Channel(void);
		Channel	&operator=(const Channel &src);

		std::vector<Client>				_allClients;
		std::string						_name;
		std::pair<bool, std::string>	_password;
};

#endif /*CHANNEL_HPP*/
