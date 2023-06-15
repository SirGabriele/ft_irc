#ifndef SERVER_HPP
# define SERVER_HPP

/*  struct sockaddr_in  */
# include <netinet/in.h>

class	Server
{
	public:
		Server(int);
		~Server(void);

		int getSocket(void) const;
	
	private:
		Server(void);
		Server(const Server &src);

		Server	&operator=(const Server &src);

		int					_socket;
		int					_reuse;
		struct sockaddr_in	_sin;
	
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
