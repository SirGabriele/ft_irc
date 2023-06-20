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

/*	select()	*/
# include <sys/select.h>

# include <iostream>
# include <string>
# include <vector>

# include "colours.hpp"
# include "Client.hpp"

# define MAX_PENDING_CON 10 //max pending connections, second argument of the listen function

class	Server
{
	public:
		Server(void);
		~Server(void);

		void	start(int);
		void	acceptNewClient(void);

		int		getSocket(void) const;
		fd_set	getReadFds(void) const;
		fd_set	getWriteFds(void) const;
		fd_set	getExceptFds(void) const;
		int		getMaxFd(void) const;

	private:
		Server(const Server &src);

		Server	&operator=(const Server &src);

		void	_initSinValues(void);
		void	_createSocket(void);
		void	_setSockOptReuseAddr(void) const;
		void	_bindSocket(void) const;
		void	_listenSocket(void) const;
		void	_closeSocket(void) const;

		std::vector<Client>	_allClients;
		struct sockaddr_in	_sin;
		fd_set				_readfds;
		fd_set				_writefds;
		fd_set				_exceptfds;
		int					_socket;
		int					_port;
		int					_nbClients;
		int					_maxFd;
	
	/*	START OF EXCEPTIONS	*/
	class	Error : public std::exception
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
