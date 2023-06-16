#ifndef SERVER_HPP
# define SERVER_HPP

/*  struct sockaddr_in  */
# include <netinet/in.h>

/*	getprotobyname()	*/
# include <netdb.h>

/*	htons()	*/
# include <arpa/inet.h>

/*	socket(), getsockopt(), bind(), listen(), accept()	*/
# include <sys/types.h>
# include <sys/socket.h>

/*	close()	*/
# include <unistd.h>

# include <iostream>
# include <string>
# include <vector>

# include "colours.hpp"
//# include "Client.hpp"

# define MAX_PENDING_CON 10 //max pending connections, second argument of the listen function

//class	Client;

class	Server
{
	public:
		Server(int);
		~Server(void);

//		int	acceptCon(void);
		int getSocket(void) const;
	
	private:
		Server(void);
		Server(const Server &src);

		Server	&operator=(const Server &src);

		void	_initSinValues(void);
		void	_createSocket(void);
		void	_setSockOptReuseAddr(void) const;
		void	_bindSocket(void) const;
		void	_listenSocket(void) const;
		void	_closeSocket(void) const;

//		std::vector<Client>	_allClients;
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

#endif /*SERVER_HPP*/
