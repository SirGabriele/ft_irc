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
# include <sstream>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <sstream>

# include "colours.hpp"
# include "Client.hpp"
# include "Channel.hpp"

/*	Hexchat text formatting	*/
# define HEX_INFO std::string("\x02[INFO]\x0F")
# define HEX_BOLD std::string("\x02")
# define HEX_RESET std::string("\x0F")

# define MAX_PENDING_CON 10 //max pending connections, second argument of the listen function
# define BUFFER_SIZE 1024

extern int	g_signal;

class	Server
{
	public:
		Server(void);
		~Server(void);

		void	start(int, const char *);
		bool	run(void);
		void	displayChannels(Client &) const;

//		int		getMaxFd(void) const;
		int		getSocket(void) const;
/*		fd_set	getReadFds(void) const;
		fd_set	getWriteFds(void) const;*/

	private:
		Server(const Server &src);

		Server	&operator=(const Server &src);

		void	_initSinValues(void);
		void	_createSocket(void);
		void	_setSockOptReuseAddr(void) const;
		void	_bindSocket(void) const;
		void	_listenSocket(void) const;
		void	_closeSocket(void) const;
		void	_shutdownServer(void);

		void	_receiveData(int);
		void	_acceptNewClient(void);
		void	_processInput(int, const char *);
		void	_detectCommand(Client &);
		void	_sendMessageToClient(const Client &, const std::string &) const;
		void	_sendMessageToChannel(const Channel &, const std::string &) const;
		void	_sendMessage(const Client &, const Client &);
		void	_join(std::istringstream &, Client &);
		void	_createChannel(const std::string &, Client &);
		void	_createChannel(const std::string &, const std::string &, Client &);
		void	_displayClient(const Client &, const std::string &) const;

		void	_nick(std::istringstream &, Client &);
		void	_user(std::istringstream &, Client &);
		void	_userHexchat(std::istringstream &, Client &);
		void	_pass(std::istringstream &, Client & client);
		bool	_isUsernameAlreadyTaken(const std::string &) const;
		void	_whois(std::istringstream &, const Client &) const;
		bool	_isChannelNameValid(const std::string &, const Client &) const;
		void	_displayChannels(std::istringstream &, const Client &) const;
		void	_privmsg(std::istringstream &, const Client & client);
		void	_quit(Client &client);
		void	_disconnectClientFromAllChannels(const std::vector<std::string> &, const std::string &);
		void		_part(std::istringstream &, Client &);
		bool		_doesChannelExist(const Client &, const std::string &) const;
		void		_removeClientFromChannel(Client &, Channel &);
		void		_shutdownChannel(Channel &);
		void		_kick(std::istringstream &, Client &);
		std::string	_extractReason(std::istringstream &) const;
		bool		_isUserOp(const Client &, const std::string &);
		void		_kickUserFromChannel(Client &, Channel &, const std::string &) const;

		const Client	&_getClient(int) const;
		int				_getClientIndex(int) const;
		int				_getClientIndex(const std::string &) const;

		void	_setPassword(const std::stringstream &, Client &);
		void	_setUsername(const std::stringstream &, Client &);
		void	_setNickname(const std::stringstream &, Client &);
		void	_setMaxFd(void);

		std::map<std::string, Channel>	_allChannels;
		std::vector<Client>				_allClients;
		struct sockaddr_in				_sin;
		std::string						_password;
		fd_set							_readfds;
		fd_set							_writefds;
		int								_socket;
		int								_port;
		int								_maxFd;
	
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
