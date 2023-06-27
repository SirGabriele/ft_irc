#ifndef CLIENT_HPP
# define CLIENT_HPP

/*  struct sockaddr_in  */
# include <netinet/in.h>

/*	getprotobyname()	*/
# include <netdb.h>

/*	close()	*/
# include <unistd.h>

# include <iostream>
# include <string>
# include <vector>

# include "colours.hpp"

class	Client
{
	public:
		Client(int);
		Client(const Client &src);
		Client	&operator=(const Client &src);
		~Client(void);

		void	closeSocket(void) const;
		void	completeInput(const char *);
		void	resetInput(void);
		void	addChannel(const std::string &);

		struct sockaddr_in					getSin(void) const;
		const std::vector<std::string>		&getAllChannels(void) const;
		const std::pair<bool, std::string>	&getNickname(void) const;
		const std::pair<bool, std::string>	&getUsername(void) const;
    bool                                getPassword(void) const;

		const std::string					&getInput(void);
		int 								getSocket(void) const;

		void	setNickname(const std::string &);
		void	setUsername(const std::string &);
		void	setPassword(bool status);
		void	setSocket(int);

	private:
		Client(void);

		void	_initSinValues(void);

		std::vector<std::string>		_allChannels;
		struct sockaddr_in				_sin;
		std::pair<bool, std::string>	_username;
		std::pair<bool, std::string>	_nickname;
    bool                          _password;
		std::string						_input;
		int								_socket;
		int								_port;

	/*	START OF EXCEPTIONS	*/
	class	Error: public std::exception
	{
		public:
			Error(const std::string &) throw();
			~Error(void) throw();
			const char	*what(void) const throw();

		private:
			const std::string	_errMsg;
	};
	/*	END OF EXCEPTIONS*/
};

#endif /*CLIENT_HPP*/
