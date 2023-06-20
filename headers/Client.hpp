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

# include "colours.hpp"

class	Client
{
	public:
		Client(int);
		Client(const Client &src);
		~Client(void);

		void	create(int);

		struct sockaddr_in	getSin(void) const;
		int 				getSocket(void) const;

		void	setSocket(int);
	
	private:
		Client(void);

		Client	&operator=(const Client &src);

		void	_initSinValues(void);
		void	_closeSocket(void) const;

		struct sockaddr_in	_sin;
		int					_socket;
		int					_port;
	
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
