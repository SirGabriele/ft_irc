#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>

# include "Client.hpp"

class	Channel
{
	public:
		Channel(void);
		Channel(const Channel &src);
		Channel(const std::string &, const std::string &);
		Channel(const std::string &, const std::string &, const std::string &);
		~Channel(void);

		void	addNewUsername(const std::string &);
		void	deleteUsername(const std::string &);
		bool	isClientMember(const std::string &) const;

		const std::string					&getName(void) const;
		const std::pair<bool, std::string>	&getPassword(void) const;
		const std::string					&getOp(void) const;
		const std::vector<std::string>		&getMemberNames(void) const;

	private:
		Channel							&operator=(const Channel &src);
		std::vector<std::string>		_memberNames;
		std::string						_name;
		std::pair<bool, std::string>	_password;
		std::string						_op;
};

#endif /*CHANNEL_HPP*/
